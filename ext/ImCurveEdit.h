#pragma once
#include <stdint.h>
#include "imgui.h"

struct ImRect;

namespace ImCurveEdit
{
    enum CurveType
    {
        CurveNone,
        CurveDiscrete,
        CurveLinear,
        CurveSmooth,
        CurveBezier,
    };

    struct EditPoint
    {
        int curveIndex;
        int pointIndex;
        bool operator <(const EditPoint& other) const
        {
            if (curveIndex < other.curveIndex)
                return true;
            if (curveIndex > other.curveIndex)
                return false;

            if (pointIndex < other.pointIndex)
                return true;
            return false;
        }
    };

    struct Delegate
    {
        virtual size_t GetCurveCount() = 0;
        virtual bool IsVisible(size_t curveIndex) { return true; }
        virtual CurveType GetCurveType(size_t curveIndex) const { return CurveLinear; }
        virtual ImVec2 GetRange() { return ImVec2(1.f, 1.f); }
        virtual ImVec2 GetMin() { return ImVec2(0, 0); }
        virtual size_t GetPointCount(size_t curveIndex) = 0;
        virtual uint32_t GetCurveColor(size_t curveIndex) = 0;
        virtual ImVec2* GetPoints(size_t curveIndex) = 0;
        virtual int EditPoint(size_t curveIndex, int pointIndex, ImVec2 value) = 0;
        virtual void AddPoint(size_t curveIndex, ImVec2 value) = 0;
        virtual unsigned int GetBackgroundColor() { return 0xFF202020; }
        // handle undo/redo thru this functions
        virtual void BeginEditing() {}
        virtual void EndEditing() {}
    };

    int Edit(Delegate &delegate, const ImVec2& size, unsigned int id, const ImRect *clippingRect = NULL, ImVector<EditPoint> *selectedPoints = NULL);
}
