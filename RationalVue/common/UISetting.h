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
	_3DGraphicsQuality m_3DGraphicsQuality;//3Dͼ������
	bool m_bEnableMagnificatoinBtn;//�Ƿ񼤻�Ŵ��ʰ�ť
};