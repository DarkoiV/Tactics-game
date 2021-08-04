#pragma once

// Tags
enum class eTAG {
	UNIT,
};

// Container holding tagged pointer
struct sTagged {
	void* pointer;
	eTAG  tag;
};
