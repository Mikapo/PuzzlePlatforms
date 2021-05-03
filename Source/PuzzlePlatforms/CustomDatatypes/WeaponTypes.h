#pragma once

enum EWeaponTypes
{
	MachineGun,
	LaserGun,
	RocketLauncher
};

struct SWeaponTypes
{
	EWeaponTypes Type;
	int32 Damage;
	int32 Durability;
};

