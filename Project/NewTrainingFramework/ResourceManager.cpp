#include "stdafx.h"
#include "ResourceManager.h"

// Administreaza resursele ce pot fi folosite in cadrul scenei:
// modele, texturi, shadere, fisiere de sunet etc...

ResourceManager* ResourceManager::Instance = NULL;