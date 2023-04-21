//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "Behavior.h"
#include "BehaviorHudText.h"
#include "Sprite.h"
#include "Stream.h"
//------------------------------------------------------------------------------
enum HudTextStates
{
  cHudTextInvalid = -1,
  // HUD Text has not yet been initialized.
  cHudTextIdle,
  // HUD Text will normally remain static.
};
class BehaviorHudText : public Behavior
{
public:
  __inline static Type type() { return Type::Behavior; }
  explicit BehaviorHudText(Entity& parent);
  void Init() override;
  void Update(float dt) override;
  void Read(Stream stream) override;
  void UpdateText();
  Component* Clone(Entity& newParent) const override;

private:
  // Add HUD Text-specific behavior variables.

  // The format string to be used with sprintf_s() when updating the HUD Text object.
  // (For example: "Score: %d")
  std::string formatString;

  // The buffer to be used with sprintf_s() when updating the HUD Text object.
  // (For example: "Score: 9001")
  // (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
  //	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
  std::string displayString;

  int scoreSystem;

  // The value currently being displayed by the HUD Text object.
  // (NOTE: This value can be compared with *watchValue to determine when the text must be updated.)
  // (NOTE: Make sure to update this value each time the text is updated.)
  unsigned displayValue;
};