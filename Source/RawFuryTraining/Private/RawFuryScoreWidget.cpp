// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "RawFuryScoreWidget.h"

#include "Widgets/Layout/SSpacer.h"

#define LOCTEXT_NAMESPACE "RawFuryTraining"

void SRawFuryScoreWidget::Construct(const FArguments& InArgs)
{
    ChildSlot
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            [
                SNew(SSpacer)
            ]

            +SHorizontalBox::Slot()
            [
                SNew(STextBlock)
                .Text(LOCTEXT("TextName", "TextName"))
                .Justification(ETextJustify::Center)
            ]

            +SHorizontalBox::Slot()
            [
                SNew(SSpacer)
            ]
        ];
}
#undef LOCTEXT_NAMESPACE