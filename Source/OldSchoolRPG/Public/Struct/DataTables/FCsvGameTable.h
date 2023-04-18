#pragma once

struct FCsvGameTable
{
protected:
	const FString CsvFileName;
	const FString CsvFilePath {""};
	const FString BaseLocation {"OldSchoolRPG/Content/Tables/CSV/"}; // todo: config this

public:
	explicit FCsvGameTable(const FString& CsvFileName, const FString& CsvFilePath = "")
		: CsvFileName(CsvFileName), CsvFilePath(CsvFilePath)
	{
	}

	FString GetFullPath() const;
};
