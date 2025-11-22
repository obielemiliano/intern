CREATE EXTENSION IF NOT EXISTS "pgcrypto";

CREATE TABLE IF NOT EXISTS candidates (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  first_name TEXT,
  last_name TEXT,
  email TEXT UNIQUE,
  phone TEXT,
  education JSONB,
  experience JSONB,
  skills TEXT[],
  source TEXT,
  resume_url TEXT,
  normalized_profile JSONB,
  score INTEGER,
  stage TEXT DEFAULT 'new',
  created_at TIMESTAMPTZ DEFAULT now(),
  updated_at TIMESTAMPTZ DEFAULT now()
);

CREATE TABLE IF NOT EXISTS vacancies (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  title TEXT,
  description TEXT,
  required_skills TEXT[],
  desired_experience INT,
  created_at TIMESTAMPTZ DEFAULT now()
);