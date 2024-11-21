#include "TowerPlaces.h"

TowerPlaces::TowerPlaces()
{
	for (int i = 0; i < TowerAmount; i++)
	{
		IsPlaceTaken[i] = false;
	}
}

void TowerPlaces::Update(int x, int y)
{

	for (int i = 0; i < TowerAmount; i++)
	{
		if (arr[i][0] == x && arr[i][1] == y)
		{
			IsPlaceTaken[i] = true;
			break;
		}
	}

}
