def individual_serializer(user) -> dict:
    return {
        "nombre": user["nombre"],
        "apellido": user["apellido"],
        "usuario": user["usuario"],
        "clave": user["clave"]
    }

def list_serial(users) -> list:
    return(individual_serializer(user) for user in users)