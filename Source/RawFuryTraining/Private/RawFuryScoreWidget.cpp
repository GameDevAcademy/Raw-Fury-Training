// GameDev Academy 2021 - RawFury Training v1.0

#include "RawFuryScoreWidget.h"

#include "Widgets/Layout/SSpacer.h"
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

namespace
{
    int PrintA(int numbersToPrint, float valueToPrint)
    {
        for (int i = 0; i < numbersToPrint; i++)
        {
            std::cout << valueToPrint;
        }

        return numbersToPrint;
    }

    int PrintB(int numbersToPrint, float valueToPrint)
    {
        std::cout << "B";

        return 0;
    }

    bool compare(int a, int b)
    {
        return a > b;
    }

    void DoStuff()
    {
        std::vector<int> myInt = { 1,2,3,4,6 };
        std::sort(myInt.begin(), myInt.end(), compare);
    }
}

void SRawFuryScoreWidget::Construct(const FArguments& InArgs)
{
    static const FTextBlockStyle ScoreTextStyle = FTextBlockStyle(FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))
        .SetFontSize(50);

    ChildSlot
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            [
                SNew(SSpacer)
            ]

            +SHorizontalBox::Slot()
            [
                SAssignNew(TextWidget, STextBlock)
                .Justification(ETextJustify::Center)
                .TextStyle(&ScoreTextStyle)
            ]
            
            +SHorizontalBox::Slot()
            [
                SNew(SSpacer)
            ]
        ];

    SetVisibility(EVisibility::HitTestInvisible);
}

void SRawFuryScoreWidget::SetWidgetText(FText Message)
{
    TextWidget->SetText(Message);
}
