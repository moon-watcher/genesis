#include "FunctionStubs.h"

#include "Debug.h"

void UpdateFunctionStub(ObjectStruct* objectStruct)
{
    PrintText("*** CALLING UPDATE FUNCTION STUB");
    PrintObjectStruct(objectStruct);
}

void DestroyFunctionStub(ObjectStruct* objectStruct)
{
    PrintText("*** CALLING DESTROY FUNCTION STUB");
    PrintObjectStruct(objectStruct);
}

void DrawFunctionStub(ObjectStruct* objectStruct)
{
    PrintText("*** CALLING DRAW FUNCTION STUB");
    PrintObjectStruct(objectStruct);
}

void CollisionFunctionStub(ObjectStruct* objectStruct, ObjectStruct* collidedObject)
{
    PrintText("*** CALLING COLLISION FUNCTION STUB");
    PrintObjectStruct(objectStruct);
    PrintObjectStruct(collidedObject);
}




