// GameDev Academy 2021 - RawFury Training v1.0

#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"

class SRawFuryScoreWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SRawFuryScoreWidget) { }
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    void SetWidgetText(FText Message);

private:
    TSharedPtr<STextBlock> TextWidget;
};
