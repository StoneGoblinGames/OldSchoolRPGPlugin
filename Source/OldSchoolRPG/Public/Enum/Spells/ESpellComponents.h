#pragma once

UENUM(BlueprintType)
namespace ESpellComponent {
	enum Component {
		Verbal UMETA(DisplayName="Verbal"),
		Somatic UMETA(DisplayName="Somatic"),
		Material UMETA(DisplayName="Material")
	};
}
