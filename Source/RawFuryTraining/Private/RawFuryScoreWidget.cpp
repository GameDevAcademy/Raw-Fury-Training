// GameDev Academy 2021 - RawFury Training v1.0

#include "RawFuryScoreWidget.h"

#include "Widgets/Layout/SSpacer.h"

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
                SNew(STextBlock)
                .Text(NSLOCTEXT("RawFury", "None", "None"))
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
