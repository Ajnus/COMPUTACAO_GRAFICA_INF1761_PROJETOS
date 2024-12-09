#include <memory>
class Node;
using NodePtr = std::shared_ptr<Node>; 

#ifndef NODE_H
#define NODE_H

#include "appearance.h"
#include "node.h"
#include "shader.h"
#include "shape.h"
#include "transform.h"
#include <glm/glm.hpp>
#include <vector>
#include <initializer_list>

class Node : public std::enable_shared_from_this<Node>
{
  std::weak_ptr<Node> m_parent;       // parent node 
  ShaderPtr m_shader;                 // associated shader
  TransformPtr m_trf;                 // associated transformation
  std::vector<AppearancePtr> m_apps;  // associated appearances
  std::vector<ShapePtr> m_shps;       // associated shapes
  std::vector<NodePtr> m_nodes;       // child nodes
protected:
  Node (ShaderPtr shader=nullptr,
        TransformPtr trf=nullptr, 
        std::initializer_list<AppearancePtr> apps={},
        std::initializer_list<ShapePtr> shps={}
       );
public:
  static NodePtr Make (ShaderPtr shader,
                       TransformPtr trf, 
                       std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       TransformPtr trf, 
                       std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       TransformPtr trf, 
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       std::initializer_list<NodePtr> nodes={});
  static NodePtr Make (ShaderPtr shader,
                       std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (ShaderPtr shader,
                       TransformPtr trf, 
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );

  static NodePtr Make (TransformPtr trf, 
                       std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (TransformPtr trf, 
                       std::initializer_list<AppearancePtr> apps={},
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<NodePtr> nodes={});
  static NodePtr Make (std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (TransformPtr trf, 
                       std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (TransformPtr trf, 
                       std::initializer_list<NodePtr> nodes
                      );
  virtual ~Node ();
  void SetShader (ShaderPtr shader);
  void SetTransform (TransformPtr trf);
  void AddAppearance (AppearancePtr app);
  void AddShape (ShapePtr shp);
  void AddNode (NodePtr node);
  void SetParent (NodePtr parent);
  NodePtr GetParent () const;
  glm::mat4 GetMatrix () const;
  glm::mat4 GetModelMatrix ();
  void Render (StatePtr st);
};

#endif