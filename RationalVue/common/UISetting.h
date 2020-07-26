#pragma once
enum _3DGraphicsQuality {
	Level1,
	Level2,
	Level3,
	Level4,
	Level5,
	Level6,
	Level7,
};
class CUISetting {
public:
	_3DGraphicsQuality m_3DGraphicsQuality;//3D图形质量
	bool m_bEnableMagnificatoinBtn;//是否激活放大倍率按钮
};