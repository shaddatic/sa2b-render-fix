#pragma once

#define arylen(arry)	(sizeof(arry) / sizeof(*arry))

void	ExtraShadowEnable();

/*
*	Sections
*/

void	RestorationSettings(const config* conf);

void	EnvMapSettings(const config* conf);

void	GetEmblemSettings(const config* conf);

void	StageMapSettings(const config* conf);

void    SkyRailSettings(const config* conf);

void	CityEscapeSettings(const config* conf);

void	AquaticMineSettings(const config* conf);

void	CannonsCoreSettings(const config* conf);

void	BossBogySettings(const config* conf);

void	CartSettings(const config* conf);