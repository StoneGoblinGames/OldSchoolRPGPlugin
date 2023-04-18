#include "FCsvGameTable.h"

FString FCsvGameTable::GetFullPath() const
{
	return BaseLocation + CsvFilePath + CsvFileName;
}
