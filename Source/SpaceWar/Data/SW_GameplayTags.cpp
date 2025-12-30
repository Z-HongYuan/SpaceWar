#include "SW_GameplayTags.h"

/*
 * 关卡状态
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_LevelState_Building, "LevelState.Building", "建造地图内/建造模式内");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_LevelState_Combat, "LevelState.Combat", "战斗地图内/战斗模式内");

/*
 * 数据标签,用于传递数据
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DataTag_FuelCost, "DataTag.FuelCost", "FuelCost/燃料消耗");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DataTag_Acceleration, "DataTag.Acceleration", "Acceleration/加速度");
