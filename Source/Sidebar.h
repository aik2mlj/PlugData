/*
 // Copyright (c) 2021-2022 Timothy Schoen
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once
#include <JuceHeader.h>

struct Console;
struct Inspector;

namespace pd
{
struct Instance;
}

enum ParameterType
{
    tString,
    tInt,
    tFloat,
    tColour,
    tBool,
    tCombo
};

enum ParameterCategory
{
    cGeneral,
    cAppearance,
    cLabel,
    cExtra
};

using ObjectParameter = std::tuple<String, ParameterType, ParameterCategory, Value*, std::vector<String>>;  // name, type and pointer to value, list of items only for combobox and bool

using ObjectParameters = std::vector<ObjectParameter>;  // List of elements and update function

struct Sidebar : public Component
{
    explicit Sidebar(pd::Instance* instance);

    ~Sidebar() override;

    void paint(Graphics& g) override;
    void paintOverChildren(Graphics& g) override;
    void resized() override;

    void mouseDown(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseMove(const MouseEvent& e) override;
    void mouseExit(const MouseEvent& e) override;

    void showParameters(ObjectParameters& params);
    void showParameters();
    void hideParameters();

    bool isShowingConsole() const noexcept;

    void showSidebar(bool show);

    void pinSidebar(bool pin);
    bool isPinned();

    void updateConsole();

   private:
    ObjectParameters lastParameters;

    Console* console;
    Inspector* inspector;

    static constexpr int dragbarWidth = 11;
    int dragStartWidth = 0;
    bool draggingSidebar = false;
    bool sidebarHidden = false;

    bool pinned = false;

    int lastWidth = 250;
};
