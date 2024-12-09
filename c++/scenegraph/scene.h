#include <memory>
class Scene;
using ScenePtr = std::shared_ptr<Scene>; 

#ifndef SCENE_H
#define SCENE_H

#include "node.h"
#include "engine.h"
#include "state.h"

class Scene : public Node
{
  NodePtr m_root;
  std::vector<EnginePtr> m_engines;
protected:
  Scene (NodePtr root);
public:
  static ScenePtr Make (NodePtr root);
  ~Scene ();
  NodePtr GetRoot () const;
  void AddEngine (EnginePtr engine);
  void Update (float dt) const;
  void Render (CameraPtr camera);
};

#endif