from pydantic import BaseModel

class User(BaseModel):
    nombre: str
    apellido: str
    usuario: str
    clave: int