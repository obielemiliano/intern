// Simple orchestrator: accepts candidate payload, calls ML parser and C++ scoring
const express = require('express');
const axios = require('axios');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());

// Config via env
const CPP_SCORER = process.env.CPP_SCORER || 'http://cpp_scoring:8081/score';
const ML_PARSER = process.env.ML_PARSER || 'http://ml_parser:8000/parse';

app.get('/health', (req, res) => res.json({ok:true}));

app.post('/api/candidates', async (req, res) => {
  const candidate = req.body;
  try {
    // 1) send to ML parser (if available) - if parser not available, assume normalized = candidate
    let normalized = candidate;
    try {
      const p = await axios.post(ML_PARSER, candidate, { timeout: 5000 });
      normalized = p.data;
    } catch (err) {
      console.warn('ML parser unreachable, proceeding with provided payload');
    }

    // 2) call C++ scoring service
    const scoringResp = await axios.post(CPP_SCORER, normalized, { timeout: 5000 });
    const score = scoringResp.data.score;

    // 3) store to DB (omitted) and return
    return res.json({ ok: true, score });
  } catch (err) {
    console.error(err.message || err);
    return res.status(500).json({ ok:false, error: err.message || 'server error' });
  }
});

app.listen(3000, () => console.log('API Orchestrator listening on 3000'));