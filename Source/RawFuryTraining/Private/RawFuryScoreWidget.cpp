// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "RawFuryScoreWidget.h"

#include "Widgets/Layout/SSpacer.h"

#define LOCTEXT_NAMESPACE "RawFuryTraining"

void SRawFuryScoreWidget::Construct(const FArguments& InArgs)
{
    ChildSlot
        [
            SNew(STextBlock)
            .Text(LOCTEXT("TextName", "TextName"))
        ];
}
#undef LOCTEXT_NAMESPACE