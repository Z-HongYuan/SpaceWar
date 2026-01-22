#pragma once

#include "NativeGameplayTags.h"

/*
 * 关卡状态
 */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_LevelState_Building);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_LevelState_Combat);

/*
 * 数据标签,用于传递数据
 */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DataTag_FuelCost);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DataTag_Acceleration);


/*
 * 单元格允许放置的类型标签
 */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Building_CellEnable_Normal); //普通建筑
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Building_CellEnable_Propeller); //推进器
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Building_CellEnable_Special); //特殊建筑
