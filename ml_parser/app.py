from fastapi import FastAPI, Request
app = FastAPI()

@app.post("/parse")
async def parse(req: Request):
    body = await req.json()
    # Retorna una versión 'normalizada' simple
    normalized = {
      "first_name": body.get("first_name"),
      "last_name": body.get("last_name"),
      "email": body.get("email"),
      "skills": body.get("skills", []),
      "experience_years": body.get("experience_years", 0)
    }
    return normalized

