#include "CsvDataTableLoader.h"

TArray<FString> CsvDataTableLoader::GetCSVFileContent(FCsvGameTable CsvGameTable)
{
	TArray<FString> Lines;
	FString CsvFile = FPaths::ProjectPluginsDir() + CsvGameTable.GetFullPath();
	if (FPaths::FileExists(CsvFile))
	{
		FFileHelper::LoadANSITextFileToStrings(*CsvFile, NULL, Lines);
	}

	return Lines;
}
