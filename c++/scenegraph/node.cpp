#include "node.h"
#include "transform.h"
#include "appearance.h"
#include "shape.h"
#include "state.h"
#include "error.h"
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

Node::Node (ShaderPtr shader, TransformPtr trf, 
            std::initializer_list<AppearancePtr> apps,
            std::initializer_list<ShapePtr> shps
           )
: m_parent(),
  m_shader(shader),
  m_trf(trf),
  m_apps(apps),
  m_shps(shps),
  m_nodes()
{
}
NodePtr Node::Make (ShaderPtr shader, 
                    TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,trf,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,trf,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    TransformPtr trf, 
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,trf,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,nullptr,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,nullptr,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,nullptr,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, 
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,nullptr,{},shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (ShaderPtr shader, TransformPtr trf, 
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(shader,trf,{},shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,trf,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,trf,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<NodePtr> nodes)
{
  NodePtr ptr(new Node(nullptr,nullptr,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,nullptr,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,nullptr,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,nullptr,{},shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,trf,{},shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}

NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,trf,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}

Node::~Node () 
{
}

void Node::SetShader (ShaderPtr shader)
{
  m_shader = shader;
}
void Node::SetTransform (TransformPtr trf)
{
  m_trf = trf;
}
void Node::AddAppearance (AppearancePtr app)
{
  m_apps.push_back(app);
}
void Node::AddShape (ShapePtr shp)
{
  m_shps.push_back(shp);
}
void Node::AddNode (NodePtr node)
{
  m_nodes.push_back(node);
  node->SetParent(shared_from_this());
}
void Node::SetParent (NodePtr parent)
{
  m_parent = parent;
}
NodePtr Node::GetParent () const
{
  return m_parent.lock();
}
glm::mat4 Node::GetMatrix () const
{
  return m_trf ? m_trf->GetMatrix() : glm::mat4(1.0f);
}
glm::mat4 Node::GetModelMatrix () 
{
  glm::mat4 mat = GetMatrix();
  NodePtr node = GetParent();
  while (node != nullptr) {
    mat = node->GetMatrix() * mat;
    node = node->GetParent();
  } 
  return mat;
}
void Node::Render (StatePtr st) 
{
  // load
  if (m_shader) 
    m_shader->Load(st);
  if (m_trf) 
    m_trf->Load(st);
  for (AppearancePtr app : m_apps)
    app->Load(st);
  // draw
  if (!m_shps.empty()) {
    st->LoadMatrices();
    for (ShapePtr shp : m_shps)
      shp->Draw(st);
  }
  for (NodePtr node : m_nodes)
    node->Render(st);
  // unload in reverse order
  for (AppearancePtr app : m_apps)
    app->Unload(st);
  if (m_trf)
    m_trf->Unload(st);
  if (m_shader)
    m_shader->Unload(st);
  Error::Check("end node render");
}
