//
// Created by maxan on 12/3/2023.
//

#include "model.h"

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader) : _shader { shader }, _mesh { mesh }{}
