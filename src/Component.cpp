//
// Created by ftfnunes on 16/03/18.
//

#include <GameObject.h>

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}