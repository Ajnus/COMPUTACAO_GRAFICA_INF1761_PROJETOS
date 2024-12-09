
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "arcball.h"
#include "scene.h"
#include "state.h"
#include "camera3d.h"
#include "material.h"
#include "texture.h"
#include "transform.h"
#include "cube.h"
#include "quad.h"
#include "sphere.h"
#include "error.h"
#include "shader.h"
#include "light.h"
#include "polyoffset.h"
#include "cylinder.h"
#include "variable.h"
#include "clipplane.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.5f, 4.0f};

static ScenePtr scene;
static Camera3DPtr camera;
static ArcballPtr arcball;

static void initialize(void)
{
  // set background color: almost black
  // glClearColor(0.06f, 0.06f, 0.06f, 1.0f);
  // dark blue
  // glClearColor(0.0f, 0.0f, 0.01f, 1.0f);
  // white
  // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  // chess brown
  // glClearColor(0.5f, 0.3f, 0.25f, 1.0f);
  // wine red
  glClearColor(0.5f, 0.0f, 0.13f, 1.0f);

  // enable clip planes
  glEnable(GL_CLIP_DISTANCE0);

  //  enable depth test
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE); // cull back faces

  // create objects
  camera = Camera3D::Make(viewer_pos[0], viewer_pos[1], viewer_pos[2]);
  // camera->SetOrtho(true);
  arcball = camera->CreateArcball();

  // LightPtr light = ObjLight::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  LightPtr light = Light::Make(0.0f, 5.0f, 0.0f, 1.0f, "world");

  AppearancePtr red = Material::Make(1.0f, 0.5f, 0.5f);
  AppearancePtr poff = PolygonOffset::Make(-1, -1);
  AppearancePtr paper = Texture::Make("decal", "../../images/paper.jpg");

  // --------------

  AppearancePtr white = Material::Make(1.0f, 1.0f, 1.0f, 0.5f);
  AppearancePtr brown = Material::Make(0.5f, 0.3f, 0.25f);
  AppearancePtr black = Material::Make(0.0f, 0.0f, 0.0f);

  AppearancePtr matteRed = Material::Make(1.0f, 0.498f, 0.490f, 1.0f); // pinkie
  // AppearancePtr matteRed = Material::Make(1.0f, 1.051f, 0.373f, 1.0f);

  // rgba(255,163,95,255)
  AppearancePtr matteGreen = Material::Make(0.757f, 0.886f, 0.678f, 1.0f);  // Greenie
  AppearancePtr matteGray = Material::Make(0.999f, 0.999f, 0.999f, 0.0f);   // Cinza
  AppearancePtr matteYellow = Material::Make(0.898f, 0.729f, 0.192f, 1.0f); // Amarelo
  AppearancePtr metalGray = Material::Make(0.75f, 0.75f, 0.75f, 1.0f);      // (you can't kill The) Metal

  AppearancePtr sphere_tex = Texture::Make("decal", "../../images/FIDE_DOUBLE.png");
  AppearancePtr wood_tex = Texture::Make("decal", "../../images/wood.jpg");
  AppearancePtr clock_tex = Texture::Make("decal", "../../images/clock.png");
  AppearancePtr sun_tex = Texture::Make("decal", "../../images/sol.jpg");

  TransformPtr trf1 = Transform::Make();
  trf1->Scale(3.0f, 0.3f, 3.0f);
  trf1->Translate(0.0f, -1.0f, 0.0f);

  // --------------

  TransformPtr trfBaseTabuleiro = Transform::Make();
  trfBaseTabuleiro->Scale(4.5f, 0.5f, 4.5f);
  trfBaseTabuleiro->Translate(0.0f, -1.0f, 0.0f);

  TransformPtr trfClockCube = Transform::Make();
  trfClockCube->Scale(0.75f, 1.0f, 2.7f);
  trfClockCube->Translate(-3.6f, 0.0f, 0.0f);

  // necessária à frente do relógio
  TransformPtr trfFrontFace = Transform::Make();
  trfFrontFace->Rotate(90.0f, 0.0f, 1.0f, 0.0f);
  trfFrontFace->Translate(-1.35f, 0.0f, -2.32f);
  trfFrontFace->Scale(2.7f, 1.0f, 1.0f);

  TransformPtr trfFIDE = Transform::Make();
  trfFIDE->Scale(0.40f, 0.40f, 0.40f);
  trfFIDE->Translate(0.0f, 9.5f, 0.0f);
  trfFIDE->Rotate(90.0f, 0.0f, 0.0f, 1.0f);

  TransformPtr trfClockWhiteDisk = Transform::Make();
  trfClockWhiteDisk->Translate(-2.319f, 0.00f, 1.15f);
  trfClockWhiteDisk->Rotate(90.0f, 0.0f, 1.0f, 0.0f);
  // trfClockWhiteDisk->Scale(0.50f, 0.50f, 0.50f);

  TransformPtr trfClockBlackDisk = Transform::Make();
  trfClockBlackDisk->Translate(-2.319f, 0.00f, -0.12f);
  trfClockBlackDisk->Rotate(90.0f, 0.0f, 1.0f, 0.0f);
  // trfClockBlackDisk->Scale(0.50f, 0.50f, 0.50f);

  TransformPtr trfSwitchWhiteBase = Transform::Make();
  trfSwitchWhiteBase->Scale(0.05f, 0.10f, 0.05f);
  trfSwitchWhiteBase->Translate(-27.0f * 2, 10.0f, 6.8f * 2);

  TransformPtr trfSwitchWhiteButton = Transform::Make();
  trfSwitchWhiteButton->Scale(0.10f, 0.10f, 0.10f);
  trfSwitchWhiteButton->Translate(-27.0f, 12.0f, 6.8f);

  TransformPtr trfSwitchBlackBase = Transform::Make();
  trfSwitchBlackBase->Scale(0.05f, 0.10f, 0.05f);
  trfSwitchBlackBase->Translate(-27.0f * 2, 10.0f, -6.4f * 2);

  TransformPtr trfswitchBlackButton = Transform::Make();
  trfswitchBlackButton->Scale(0.10f, 0.10f, 0.10f);
  trfswitchBlackButton->Translate(-27.0f, 12.0f, -6.4f);

  TransformPtr trfSwitchButtonWhiteTopCap = Transform::Make();
  trfSwitchButtonWhiteTopCap->Scale(0.10f, 0.10f, 0.10f);
  trfSwitchButtonWhiteTopCap->Translate(-27.0f, 12.3f, 6.8f);
  trfSwitchButtonWhiteTopCap->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

  TransformPtr trfSwitchButtonBlackTopCap = Transform::Make();
  trfSwitchButtonBlackTopCap->Scale(0.10f, 0.10f, 0.10f);
  trfSwitchButtonBlackTopCap->Translate(-27.0f, 12.3f, -6.4f);
  trfSwitchButtonBlackTopCap->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

  TransformPtr trfSwitchButtonWhiteBottomCap = Transform::Make();
  trfSwitchButtonWhiteBottomCap->Scale(0.10f, 0.10f, 0.10f);
  trfSwitchButtonWhiteBottomCap->Translate(-27.0f, 12.0f, 6.8f);
  trfSwitchButtonWhiteBottomCap->Rotate(90.0f, 1.0f, 0.0f, 0.0f);

  TransformPtr trfSwitchButtonBlackBottomCap = Transform::Make();
  trfSwitchButtonBlackBottomCap->Scale(0.10f, 0.10f, 0.10f);
  trfSwitchButtonBlackBottomCap->Translate(-27.0f, 12.0f, -6.4f);
  trfSwitchButtonBlackBottomCap->Rotate(90.0f, 1.0f, 0.0f, 0.0f);

  // --------------

  ShapePtr baseTabuleiro = Cube::Make();
  Error::Check("after Cube::Make()");

  ShapePtr clockCube = Cube::Make();
  Error::Check("after Cube::Make()");

  ShapePtr frontFace = Quad::Make();
  Error::Check("after Quad::Make()");

  ShapePtr sphere = Sphere::Make();
  Error::Check("after shps");

  ShapePtr switchWhiteBase = Cylinder::Make();
  Error::Check("after Cylinder::Make()");

  ShapePtr switchWhiteButton = Cylinder::Make(64, 64, 1.0f, 0.5f);
  Error::Check("after Cylinder::Make()");

  ShapePtr switchBlackBase = Cylinder::Make();
  Error::Check("after Cylinder::Make()");

  ShapePtr switchBlackButton = Cylinder::Make(64, 64, 1.0f, 0.5f);
  Error::Check("after Cylinder::Make()");

  ShapePtr clockWhiteDisk = Quad::Make();
  Error::Check("after Disk::Make()");

  ShapePtr clockBlackDisk = Quad::Make();
  Error::Check("after Disk::Make()");

  ShapePtr cylinder2 = Cylinder::Make(64, 64, 1.0f, 7.0f);
  Error::Check("after Cylinder::Make()");

  ShapePtr switchButtonWhiteTopCap = Disk::Make();
  Error::Check("after Disk::Make()");

  ShapePtr switchButtonBlackTopCap = Disk::Make();
  Error::Check("after Disk::Make()");

  ShapePtr switchButtonWhiteBottomCap = Disk::Make();
  Error::Check("after Disk::Make()");

  ShapePtr switchButtonBlackBottomCap = Disk::Make();
  Error::Check("after Disk::Make()");

  // Lista de nós para o tabuleiro
  std::vector<NodePtr> chessboardNodes;

  // Tamanho relativo dos quadrados menores
  float squareSize = 4.5f / 8.0f;   // Reduzido proporcional ao quad grande
  float offset = squareSize / 1.3f; // Correção de posicionamento para centralizar os quadrados

  // Criação dos quadrados do tabuleiro
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      // Apenas para quadrados verdes (posições alternadas)
      if ((i + j) % 2 == 1)
      {
        TransformPtr trfSquare = Transform::Make();
        trfSquare->Scale(squareSize, 1.0f, squareSize); // Escala reduzida para cada quadrado
        trfSquare->Translate(
            -1.17f * 4.5f + squareSize * 0.5f * 4.5f + i * (squareSize + offset), // X-posição
            0.01f,                                                                // Elevação mínima para evitar z-fighting
            -0.94f * 4.5f + squareSize * 0.5f * 4.5f + j * (squareSize + offset)  // Z-posição
        );
        trfSquare->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

        ShapePtr square = Quad::Make(1, 1);
        chessboardNodes.push_back(Node::Make(trfSquare, {matteGreen}, {square}));
      }
    }
  }

  // Lista de peões brancos para o tabuleiro
  std::vector<NodePtr> Pawns;

  float PawnBaseOffset = 3.75f;
  float PawnSphereOffset = 5.625f;
  float whiteToBlackPawnBaseOffset = 5.625f * 3.33f;
  float whiteToBlackPawnSphereOffset = 5.625f * 5;

  // Criação dos peões brancos no tabuleiro
  for (int i = 0; i < 8; ++i)
  {
    TransformPtr trfPawnSphere = Transform::Make();
    trfPawnSphere->Scale(0.20f / 2, 0.20f / 2, 0.20f / 2);
    trfPawnSphere->Translate(19.65f - i * PawnSphereOffset, 4.01f, 14.15f);

    TransformPtr trfPawnDisk = Transform::Make();
    trfPawnDisk->Scale(0.30f / 2, 0.30f / 2, 0.30f / 2);
    trfPawnDisk->Translate(13.1f - i * PawnBaseOffset, 2.0f, 9.4f);
    trfPawnDisk->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

    TransformPtr trfPawnBase = Transform::Make();
    trfPawnBase->Scale(0.30f / 2, 0.30f / 2, 0.30f / 2);
    trfPawnBase->Translate(13.1f - i * PawnBaseOffset, 0.0f, 9.4f);

    ShapePtr pawnSphere = Sphere::Make();
    ShapePtr pawnDisk = Disk::Make();
    ShapePtr pawnBase = Cylinder::Make(64, 64, 0.75f, 2.0f, 0.5f);

    Pawns.push_back(Node::Make(trfPawnSphere, {white}, {pawnSphere}));
    Pawns.push_back(Node::Make(trfPawnDisk, {white}, {pawnDisk}));
    Pawns.push_back(Node::Make(trfPawnBase, {white}, {pawnBase}));
  }

  // Criação dos peões negros no tabuleiro
  for (int j = 0; j < 8; ++j)
  {
    TransformPtr trfPawnSphere = Transform::Make();
    trfPawnSphere->Scale(0.20f / 2, 0.20f / 2, 0.20f / 2);
    trfPawnSphere->Translate(19.65f - j * PawnSphereOffset, 4.01f, 14.15f - whiteToBlackPawnSphereOffset);

    TransformPtr trfPawnDisk = Transform::Make();
    trfPawnDisk->Scale(0.30f / 2, 0.30f / 2, 0.30f / 2);
    trfPawnDisk->Translate(13.1f - j * PawnBaseOffset, 2.0f, 9.4f - whiteToBlackPawnBaseOffset);
    trfPawnDisk->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

    TransformPtr trfPawnBase = Transform::Make();
    trfPawnBase->Scale(0.30f / 2, 0.30f / 2, 0.30f / 2);
    trfPawnBase->Translate(13.1f - j * PawnBaseOffset, 0.0f, 9.4f - whiteToBlackPawnBaseOffset);

    ShapePtr pawnSphere = Sphere::Make();
    ShapePtr pawnDisk = Disk::Make();
    ShapePtr pawnBase = Cylinder::Make(64, 64, 0.75f, 2.0f, 0.5f);

    Pawns.push_back(Node::Make(trfPawnSphere, {black}, {pawnSphere}));
    Pawns.push_back(Node::Make(trfPawnDisk, {black}, {pawnDisk}));
    Pawns.push_back(Node::Make(trfPawnBase, {black}, {pawnBase}));
  }

  // Criação da Platéia
  // Initialize random seed
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  // Lista de peões para a plateia
  std::vector<NodePtr> audiencePawns;

  float audiencePawnBaseOffset = 3.75f;
  float audiencePawnSphereOffset = 5.625f;

  float audienceOffsetX = 17.0f; // 5.625f * 3.33f;
  float audienceOffsetZ = -9.3f; // 14.15f + 5.625f * 3.33f; // Offset to the right of the board

  // Criação dos peões da plateia
  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 6; ++j)
    {
      TransformPtr trfPawnSphere = Transform::Make();
      trfPawnSphere->Scale(0.20f, 0.20f, 0.20f);
      trfPawnSphere->Translate(audienceOffsetX + 8.5f + i * audiencePawnSphereOffset, 4.01f, audienceOffsetZ - 4.65f + j * audiencePawnSphereOffset);

      TransformPtr trfPawnDisk = Transform::Make();
      trfPawnDisk->Scale(0.30f, 0.30f, 0.30f);
      trfPawnDisk->Translate(audienceOffsetX + i * audiencePawnBaseOffset, 2.0f, audienceOffsetZ + j * audiencePawnBaseOffset);
      trfPawnDisk->Rotate(90.0f, -1.0f, 0.0f, 0.0f);

      TransformPtr trfPawnBase = Transform::Make();
      trfPawnBase->Scale(0.30f, 0.30f, 0.30f);
      trfPawnBase->Translate(audienceOffsetX + i * audiencePawnBaseOffset, 0.0f, audienceOffsetZ + j * audiencePawnBaseOffset);

      ShapePtr pawnSphere = Sphere::Make();
      ShapePtr pawnDisk = Disk::Make();
      ShapePtr pawnBase = Cylinder::Make(64, 64, 0.75f, 2.0f, 0.5f);

      AppearancePtr crowdColor = Material::Make(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX), static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX), static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));

      audiencePawns.push_back(Node::Make(trfPawnSphere, {crowdColor}, {pawnSphere}));
      audiencePawns.push_back(Node::Make(trfPawnDisk, {crowdColor}, {pawnDisk}));
      audiencePawns.push_back(Node::Make(trfPawnBase, {crowdColor}, {pawnBase}));
    }
  }

  // create shaders
  ShaderPtr shader = Shader::Make(light, "world");
  shader->AttachVertexShader("../../shaders/ilum_frag/vertex.glsl");
  shader->AttachFragmentShader("../../shaders/ilum_frag/fragment.glsl");
  shader->Link();

  ShaderPtr shd_tex = Shader::Make(light, "camera");
  shd_tex->AttachVertexShader("../../shaders/texture/vertex.glsl");
  shd_tex->AttachFragmentShader("../../shaders/texture/fragment.glsl");
  shd_tex->Link();

  ShaderPtr shd_clip = Shader::Make(light, "camera");
  shd_clip->AttachVertexShader("../../shaders/clipplane/vertex.glsl");
  shd_clip->AttachFragmentShader("../../shaders/clipplane/fragment.glsl");
  shd_clip->Link();

  // Fog parameters
  auto fcolor = Variable<glm::vec4>::Make("fcolor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  auto fdensity = Variable<float>::Make("fdensity", 0.060f);
  auto fstart = Variable<float>::Make("fstart", 300.0f);
  TransformPtr trfFog = Transform::Make();
  trfFog->Translate(600.0f, 1.0f, 600.0f);

  // Plano de Corte
  ClipPlanePtr clipPlane = ClipPlane::Make("clipPlane", 1.0f, 0.0f, 0.0f, 0.0f);
  //clipPlane->AddPlane(1.0f, 0.0f, 0.0f, 0.0f);

  // Configure o estado
  // StatePtr state = State::Make(camera);
  // state->PushShader(shd_clip);
  // state->SetTexture(sphere_tex);
  // clipPlane->Load(state); // Carregue o plano de corte no estado

  // build scene
  NodePtr root = Node::Make(shader,
                            {
                                Node::Make(trfBaseTabuleiro, {white, matteGray}, {baseTabuleiro}),
                                Node::Make({white, matteGreen}, {chessboardNodes[0]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[1]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[2]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[3]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[4]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[5]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[6]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[7]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[8]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[9]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[10]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[11]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[12]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[13]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[14]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[15]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[16]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[17]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[18]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[19]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[20]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[21]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[22]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[23]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[24]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[25]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[26]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[27]}),

                                Node::Make({white, matteGreen}, {chessboardNodes[28]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[29]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[30]}),
                                Node::Make({white, matteGreen}, {chessboardNodes[31]}),

                                // Peão cheio de 3 em 3, 1 nó para cada peão gerava transformações inadequadas
                                // Peões brancos
                                Node::Make(shd_tex, {Pawns[0]}),
                                Node::Make(shd_tex, {Pawns[1]}),
                                Node::Make(shd_tex, {Pawns[2]}),
                                Node::Make(shd_tex, {Pawns[3]}),
                                Node::Make(shd_tex, {Pawns[4]}),
                                Node::Make(shd_tex, {Pawns[5]}),
                                Node::Make(shd_tex, {Pawns[6]}),
                                Node::Make(shd_tex, {Pawns[7]}),
                                Node::Make(shd_tex, {Pawns[8]}),
                                Node::Make(shd_tex, {Pawns[9]}),
                                Node::Make(shd_tex, {Pawns[10]}),
                                Node::Make(shd_tex, {Pawns[11]}),
                                Node::Make(shd_tex, {Pawns[12]}),
                                Node::Make(shd_tex, {Pawns[13]}),
                                Node::Make(shd_tex, {Pawns[14]}),
                                Node::Make(shd_tex, {Pawns[15]}),
                                Node::Make(shd_tex, {Pawns[16]}),
                                Node::Make(shd_tex, {Pawns[17]}),
                                Node::Make(shd_tex, {Pawns[18]}),
                                Node::Make(shd_tex, {Pawns[19]}),
                                Node::Make(shd_tex, {Pawns[20]}),
                                Node::Make(shd_tex, {Pawns[21]}),
                                Node::Make(shd_tex, {Pawns[22]}),
                                Node::Make(shd_tex, {Pawns[23]}),

                                // Peões negros
                                Node::Make(shd_tex, {Pawns[24]}),
                                Node::Make(shd_tex, {Pawns[25]}),
                                Node::Make(shd_tex, {Pawns[26]}),
                                Node::Make(shd_tex, {Pawns[27]}),
                                Node::Make(shd_tex, {Pawns[28]}),
                                Node::Make(shd_tex, {Pawns[29]}),
                                Node::Make(shd_tex, {Pawns[30]}),
                                Node::Make(shd_tex, {Pawns[31]}),
                                Node::Make(shd_tex, {Pawns[32]}),
                                Node::Make(shd_tex, {Pawns[33]}),
                                Node::Make(shd_tex, {Pawns[34]}),
                                Node::Make(shd_tex, {Pawns[35]}),
                                Node::Make(shd_tex, {Pawns[36]}),
                                Node::Make(shd_tex, {Pawns[37]}),
                                Node::Make(shd_tex, {Pawns[38]}),
                                Node::Make(shd_tex, {Pawns[39]}),
                                Node::Make(shd_tex, {Pawns[40]}),
                                Node::Make(shd_tex, {Pawns[41]}),
                                Node::Make(shd_tex, {Pawns[42]}),
                                Node::Make(shd_tex, {Pawns[43]}),
                                Node::Make(shd_tex, {Pawns[44]}),
                                Node::Make(shd_tex, {Pawns[45]}),
                                Node::Make(shd_tex, {Pawns[46]}),
                                Node::Make(shd_tex, {Pawns[47]}),

                                // Platéia
                                Node::Make(shd_tex, {audiencePawns[0]}),
                                Node::Make(shd_tex, {audiencePawns[1]}),
                                Node::Make(shd_tex, {audiencePawns[2]}),
                                Node::Make(shd_tex, {audiencePawns[3]}),
                                Node::Make(shd_tex, {audiencePawns[4]}),
                                Node::Make(shd_tex, {audiencePawns[5]}),
                                Node::Make(shd_tex, {audiencePawns[6]}),
                                Node::Make(shd_tex, {audiencePawns[7]}),
                                Node::Make(shd_tex, {audiencePawns[8]}),
                                Node::Make(shd_tex, {audiencePawns[9]}),
                                Node::Make(shd_tex, {audiencePawns[10]}),
                                Node::Make(shd_tex, {audiencePawns[11]}),
                                Node::Make(shd_tex, {audiencePawns[12]}),
                                Node::Make(shd_tex, {audiencePawns[13]}),
                                Node::Make(shd_tex, {audiencePawns[14]}),
                                Node::Make(shd_tex, {audiencePawns[15]}),
                                Node::Make(shd_tex, {audiencePawns[16]}),
                                Node::Make(shd_tex, {audiencePawns[17]}),
                                Node::Make(shd_tex, {audiencePawns[18]}),
                                Node::Make(shd_tex, {audiencePawns[19]}),
                                Node::Make(shd_tex, {audiencePawns[20]}),
                                Node::Make(shd_tex, {audiencePawns[21]}),
                                Node::Make(shd_tex, {audiencePawns[22]}),
                                Node::Make(shd_tex, {audiencePawns[23]}),
                                Node::Make(shd_tex, {audiencePawns[24]}),
                                Node::Make(shd_tex, {audiencePawns[25]}),
                                Node::Make(shd_tex, {audiencePawns[26]}),
                                Node::Make(shd_tex, {audiencePawns[27]}),
                                Node::Make(shd_tex, {audiencePawns[28]}),
                                Node::Make(shd_tex, {audiencePawns[29]}),
                                // Platéia - continuação

                                Node::Make(shd_tex, {audiencePawns[30]}),
                                Node::Make(shd_tex, {audiencePawns[31]}),
                                Node::Make(shd_tex, {audiencePawns[32]}),
                                Node::Make(shd_tex, {audiencePawns[33]}),
                                Node::Make(shd_tex, {audiencePawns[34]}),
                                Node::Make(shd_tex, {audiencePawns[35]}),
                                Node::Make(shd_tex, {audiencePawns[36]}),
                                Node::Make(shd_tex, {audiencePawns[37]}),
                                Node::Make(shd_tex, {audiencePawns[38]}),
                                Node::Make(shd_tex, {audiencePawns[39]}),
                                Node::Make(shd_tex, {audiencePawns[40]}),
                                Node::Make(shd_tex, {audiencePawns[41]}),
                                Node::Make(shd_tex, {audiencePawns[42]}),
                                Node::Make(shd_tex, {audiencePawns[43]}),
                                Node::Make(shd_tex, {audiencePawns[44]}),
                                Node::Make(shd_tex, {audiencePawns[45]}),
                                Node::Make(shd_tex, {audiencePawns[46]}),
                                Node::Make(shd_tex, {audiencePawns[47]}),
                                Node::Make(shd_tex, {audiencePawns[48]}),
                                Node::Make(shd_tex, {audiencePawns[49]}),
                                Node::Make(shd_tex, {audiencePawns[50]}),
                                Node::Make(shd_tex, {audiencePawns[51]}),
                                Node::Make(shd_tex, {audiencePawns[52]}),
                                Node::Make(shd_tex, {audiencePawns[53]}),
                                Node::Make(shd_tex, {audiencePawns[54]}),
                                Node::Make(shd_tex, {audiencePawns[55]}),
                                Node::Make(shd_tex, {audiencePawns[56]}),
                                Node::Make(shd_tex, {audiencePawns[57]}),
                                Node::Make(shd_tex, {audiencePawns[58]}),
                                Node::Make(shd_tex, {audiencePawns[60]}),
                                Node::Make(shd_tex, {audiencePawns[61]}),
                                Node::Make(shd_tex, {audiencePawns[62]}),
                                Node::Make(shd_tex, {audiencePawns[63]}),
                                Node::Make(shd_tex, {audiencePawns[64]}),
                                Node::Make(shd_tex, {audiencePawns[65]}),
                                Node::Make(shd_tex, {audiencePawns[66]}),
                                Node::Make(shd_tex, {audiencePawns[67]}),
                                Node::Make(shd_tex, {audiencePawns[68]}),
                                Node::Make(shd_tex, {audiencePawns[69]}),
                                Node::Make(shd_tex, {audiencePawns[70]}),
                                Node::Make(shd_tex, {audiencePawns[71]}),
                                Node::Make(shd_tex, {audiencePawns[72]}),
                                Node::Make(shd_tex, {audiencePawns[73]}),
                                Node::Make(shd_tex, {audiencePawns[74]}),
                                Node::Make(shd_tex, {audiencePawns[75]}),
                                Node::Make(shd_tex, {audiencePawns[76]}),
                                Node::Make(shd_tex, {audiencePawns[77]}),
                                Node::Make(shd_tex, {audiencePawns[78]}),
                                Node::Make(shd_tex, {audiencePawns[79]}),
                                Node::Make(shd_tex, {audiencePawns[80]}),
                                Node::Make(shd_tex, {audiencePawns[81]}),
                                Node::Make(shd_tex, {audiencePawns[82]}),
                                Node::Make(shd_tex, {audiencePawns[83]}),
                                Node::Make(shd_tex, {audiencePawns[84]}),
                                Node::Make(shd_tex, {audiencePawns[85]}),
                                Node::Make(shd_tex, {audiencePawns[86]}),
                                Node::Make(shd_tex, {audiencePawns[87]}),
                                Node::Make(shd_tex, {audiencePawns[88]}),
                                Node::Make(shd_tex, {audiencePawns[89]}),
                                Node::Make(shd_tex, {audiencePawns[90]}),
                                Node::Make(shd_tex, {audiencePawns[91]}),
                                Node::Make(shd_tex, {audiencePawns[92]}),
                                Node::Make(shd_tex, {audiencePawns[93]}),
                                Node::Make(shd_tex, {audiencePawns[94]}),
                                Node::Make(shd_tex, {audiencePawns[95]}),
                                Node::Make(shd_tex, {audiencePawns[96]}),
                                Node::Make(shd_tex, {audiencePawns[97]}),
                                Node::Make(shd_tex, {audiencePawns[98]}),
                                Node::Make(shd_tex, {audiencePawns[99]}),
                                Node::Make(shd_tex, {audiencePawns[100]}),
                                Node::Make(shd_tex, {audiencePawns[101]}),
                                Node::Make(shd_tex, {audiencePawns[102]}),
                                Node::Make(shd_tex, {audiencePawns[103]}),
                                Node::Make(shd_tex, {audiencePawns[104]}),
                                Node::Make(shd_tex, {audiencePawns[105]}),
                                Node::Make(shd_tex, {audiencePawns[106]}),
                                Node::Make(shd_tex, {audiencePawns[107]}),
                                Node::Make(shd_tex, {audiencePawns[108]}),
                                Node::Make(shd_tex, {audiencePawns[109]}),
                                Node::Make(shd_tex, {audiencePawns[110]}),
                                Node::Make(shd_tex, {audiencePawns[111]}),
                                Node::Make(shd_tex, {audiencePawns[112]}),
                                Node::Make(shd_tex, {audiencePawns[113]}),
                                Node::Make(shd_tex, {audiencePawns[114]}),
                                Node::Make(shd_tex, {audiencePawns[115]}),
                                Node::Make(shd_tex, {audiencePawns[116]}),
                                Node::Make(shd_tex, {audiencePawns[117]}),
                                Node::Make(shd_tex, {audiencePawns[118]}),
                                Node::Make(shd_tex, {audiencePawns[119]}),
                                Node::Make(shd_tex, {audiencePawns[120]}),
                                Node::Make(shd_tex, {audiencePawns[121]}),
                                Node::Make(shd_tex, {audiencePawns[122]}),
                                Node::Make(shd_tex, {audiencePawns[123]}),
                                Node::Make(shd_tex, {audiencePawns[124]}),
                                Node::Make(shd_tex, {audiencePawns[125]}),
                                Node::Make(shd_tex, {audiencePawns[126]}),
                                Node::Make(shd_tex, {audiencePawns[127]}),
                                Node::Make(shd_tex, {audiencePawns[128]}),
                                Node::Make(shd_tex, {audiencePawns[129]}),
                                Node::Make(shd_tex, {audiencePawns[130]}),
                                Node::Make(shd_tex, {audiencePawns[131]}),
                                Node::Make(shd_tex, {audiencePawns[132]}),
                                Node::Make(shd_tex, {audiencePawns[133]}),
                                Node::Make(shd_tex, {audiencePawns[134]}),
                                Node::Make(shd_tex, {audiencePawns[135]}),
                                Node::Make(shd_tex, {audiencePawns[136]}),
                                Node::Make(shd_tex, {audiencePawns[137]}),
                                Node::Make(shd_tex, {audiencePawns[138]}),
                                Node::Make(shd_tex, {audiencePawns[139]}),
                                Node::Make(shd_tex, {audiencePawns[140]}),
                                Node::Make(shd_tex, {audiencePawns[141]}),
                                Node::Make(shd_tex, {audiencePawns[142]}),
                                Node::Make(shd_tex, {audiencePawns[143]}),
                                Node::Make(shd_tex, {audiencePawns[144]}),
                                Node::Make(shd_tex, {audiencePawns[145]}),
                                Node::Make(shd_tex, {audiencePawns[146]}),
                                Node::Make(shd_tex, {audiencePawns[147]}),
                                Node::Make(shd_tex, {audiencePawns[148]}),
                                Node::Make(shd_tex, {audiencePawns[150]}),
                                Node::Make(shd_tex, {audiencePawns[151]}),
                                Node::Make(shd_tex, {audiencePawns[152]}),
                                Node::Make(shd_tex, {audiencePawns[153]}),
                                Node::Make(shd_tex, {audiencePawns[154]}),
                                Node::Make(shd_tex, {audiencePawns[155]}),
                                Node::Make(shd_tex, {audiencePawns[156]}),
                                Node::Make(shd_tex, {audiencePawns[157]}),
                                Node::Make(shd_tex, {audiencePawns[158]}),
                                Node::Make(shd_tex, {audiencePawns[159]}),
                                Node::Make(shd_tex, {audiencePawns[160]}),
                                Node::Make(shd_tex, {audiencePawns[161]}),
                                Node::Make(shd_tex, {audiencePawns[162]}),
                                Node::Make(shd_tex, {audiencePawns[163]}),
                                Node::Make(shd_tex, {audiencePawns[164]}),
                                Node::Make(shd_tex, {audiencePawns[165]}),
                                Node::Make(shd_tex, {audiencePawns[166]}),
                                Node::Make(shd_tex, {audiencePawns[167]}),
                                Node::Make(shd_tex, {audiencePawns[168]}),
                                Node::Make(shd_tex, {audiencePawns[169]}),
                                Node::Make(shd_tex, {audiencePawns[170]}),
                                Node::Make(shd_tex, {audiencePawns[171]}),
                                Node::Make(shd_tex, {audiencePawns[172]}),
                                Node::Make(shd_tex, {audiencePawns[173]}),
                                Node::Make(shd_tex, {audiencePawns[174]}),
                                Node::Make(shd_tex, {audiencePawns[175]}),
                                Node::Make(shd_tex, {audiencePawns[176]}),
                                Node::Make(shd_tex, {audiencePawns[177]}),
                                Node::Make(shd_tex, {audiencePawns[178]}),
                                Node::Make(shd_tex, {audiencePawns[179]}),

                                Node::Make(shader, trfClockCube, {matteYellow}, {clockCube}),
                                Node::Make(shader, trfFrontFace, {black}, {frontFace}),
                                Node::Make(shd_clip, trfFIDE, {clipPlane, white, sphere_tex}, {sphere}),
                                // Node::Make(trf3, {white, matteGreen}, {sphere2}),
                                Node::Make(shd_tex, trfClockWhiteDisk, {white, clock_tex}, {clockWhiteDisk}),
                                Node::Make(shd_tex, trfClockBlackDisk, {white, clock_tex}, {clockBlackDisk}),
                                Node::Make(shader, trfSwitchWhiteBase, {metalGray}, {switchWhiteBase}),
                                Node::Make(shader, trfSwitchBlackBase, {metalGray}, {switchBlackBase}),
                                Node::Make(shader, trfSwitchWhiteButton, {metalGray}, {switchWhiteButton}),
                                Node::Make(shader, trfswitchBlackButton, {metalGray}, {switchBlackButton}),
                                Node::Make(shd_tex, trfSwitchButtonWhiteTopCap, {metalGray, wood_tex}, {switchButtonWhiteTopCap}),
                                Node::Make(shd_tex, trfSwitchButtonBlackTopCap, {metalGray, wood_tex}, {switchButtonBlackTopCap}),
                                Node::Make(shd_tex, trfSwitchButtonWhiteBottomCap, {metalGray, wood_tex}, {switchButtonWhiteBottomCap}),
                                Node::Make(shd_tex, trfSwitchButtonBlackBottomCap, {metalGray, wood_tex}, {switchButtonBlackBottomCap}),
                                Node::Make(shd_tex, trfFog, {fcolor, fdensity}),
                                // Node::Make(trf1, {red, decal}, {cube}),
                                // Node::Make(, {fcolor, fdensity}),
                            });
  scene = Scene::Make(root);
}

static void display(GLFWwindow *win)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
  Error::Check("before render");
  scene->Render(camera);
  Error::Check("after render");
}

static void error(int code, const char *msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
}

static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize(GLFWwindow *win, int width, int height)
{
  glViewport(0, 0, width, height);
}

static void cursorpos(GLFWwindow *win, double x, double y)
{
  // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
  int wn_w, wn_h, fb_w, fb_h;
  glfwGetWindowSize(win, &wn_w, &wn_h);
  glfwGetFramebufferSize(win, &fb_w, &fb_h);
  x = x * fb_w / wn_w;
  y = (wn_h - y) * fb_h / wn_h;
  arcball->AccumulateMouseMotion(x, y);
}
static void cursorinit(GLFWwindow *win, double x, double y)
{
  // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
  int wn_w, wn_h, fb_w, fb_h;
  glfwGetWindowSize(win, &wn_w, &wn_h);
  glfwGetFramebufferSize(win, &fb_w, &fb_h);
  x = x * fb_w / wn_w;
  y = (wn_h - y) * fb_h / wn_h;
  arcball->InitMouseMotion(x, y);
  glfwSetCursorPosCallback(win, cursorpos); // cursor position callback
}
static void mousebutton(GLFWwindow *win, int button, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    glfwSetCursorPosCallback(win, cursorinit); // cursor position callback
  }
  else                                      // GLFW_RELEASE
    glfwSetCursorPosCallback(win, nullptr); // callback disabled
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwSetErrorCallback(error);

  GLFWwindow *win = glfwCreateWindow(600, 400, "P2: Cena 3D com técnicas de renderização", nullptr, nullptr);
  glfwSetWindowAttrib(win, GLFW_FLOATING, GLFW_TRUE); // always on top
  glfwSetFramebufferSizeCallback(win, resize);        // resize callback
  glfwSetKeyCallback(win, keyboard);                  // keyboard callback
  glfwSetMouseButtonCallback(win, mousebutton);       // mouse button callback

  glfwMakeContextCurrent(win);

#ifdef __glad_h_
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD OpenGL context\n");
    exit(1);
  }
#endif
#ifdef __glew_h__
  glewInit();
  if (glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW OpenGL context\n");
    exit(1);
  }
#endif

  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  // Get the primary monitor's video mode
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  if (mode)
  // Set the window position to cover the entire width of the monitor
  {
    int windowWidth = mode->width;
    int windowHeight = 565;
    int xpos = 0;
    int ypos = (mode->height - windowHeight) / 2 - 115;
    glfwSetWindowPos(win, xpos, ypos);
    glfwSetWindowSize(win, windowWidth, windowHeight);
  }

  initialize();

  while (!glfwWindowShouldClose(win))
  {
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}