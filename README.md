# 📌 Automatización del Proceso de Atracción de Interns

## 🚀 Proyecto: Plataforma de Automatización para Atracción de Interns

Este proyecto es una plataforma diseñada para **automatizar, agilizar y estandarizar** el proceso de evaluación de candidatos para internships.  
Su propósito es reducir tiempo operativo, eliminar actividades repetitivas y generar evaluaciones más objetivas y consistentes.

El sistema está compuesto por tres servicios que trabajan juntos, cada uno con una responsabilidad específica.

---

## 🧩 Arquitectura del Proyecto

### **1. API Principal (Node.js + Express)**  
Servicio encargado de coordinar todo el flujo:

- Recibe los datos del candidato  
- Envía información al módulo de Machine Learning  
- Solicita la puntuación al motor de scoring  
- Devuelve el resultado final  

**Puerto:** 3000  
**Endpoint de salud:** `/health`

---

### **2. Módulo de Machine Learning / NLP (Python + FastAPI)**  

Servicio que procesa texto y genera características para la evaluación:

- Limpieza y análisis de texto  
- Extracción de información clave  
- Preparación de datos para el servicio de scoring  

**Puerto:** 8000  
**Docs:** `/docs`

---

### **3. Motor de Scoring (C++ con Crow)**  

Servicio de alto rendimiento que calcula la puntuación final del candidato.  

- Implementado en C++ para máxima velocidad  
- Usa Crow como microframework web  
- Recibe datos del módulo de ML y genera un puntaje  

**Puerto:** 8081  
**Endpoint de salud:** `/health`

---

## 🐳 Docker y Orquestación

El proyecto usa Docker y Docker Compose para ejecutar los 3 servicios fácilmente.

Para levantar todo el sistema:

```bash
docker compose up --build
```

---

## 🧑‍💻 Tecnologías utilizadas

- Node.js (API principal)
- Python + FastAPI (Procesamiento de lenguaje)
- C++ + Crow (Motor de scoring)
- Docker & Docker Compose
- GitHub Actions (Integración continua)