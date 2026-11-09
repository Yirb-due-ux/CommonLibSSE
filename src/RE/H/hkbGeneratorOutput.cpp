#include "RE/H/hkbGeneratorOutput.h"

#include "REL/Relocation.h"

#ifndef SKYRIM_SUPPORT_AE
namespace RE
{
	void hkbGeneratorOutput::CopyTracksFrom(const hkbGeneratorOutput& a_source)
	{
		using func_t = void (*)(const hkbGeneratorOutput&, hkbGeneratorOutput&);
		static REL::Relocation<func_t> func{ REL::ID(58633) };
		func(a_source, *this);
	}

	void hkbGeneratorOutput::BlendPoses(const hkQsTransform* a_from, const hkBitField* a_fromMask,
		const hkQsTransform* a_to, const hkBitField* a_toMask, std::int32_t a_bones,
		float a_weight, hkQsTransform* a_output, hkBitField* a_outputMask)
	{
		static REL::Relocation<decltype(&hkbGeneratorOutput::BlendPoses)> func{ REL::ID(58648) };
		func(a_from, a_fromMask, a_to, a_toMask, a_bones, a_weight, a_output, a_outputMask);
	}
}
#endif
