#include "Picture.hpp"

void LoadMino(int* handle) {

	//ƒ~ƒm‰æ‘œ“Ç‚İ‚İ
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);

	for (int i = 11; i < 18; i++) {
		//Grounded_Zƒ~ƒm(handle[11])‚©‚çGrounded_Tƒ~ƒm(handle[17])‚Ü‚Å‚ÍC
		//Zƒ~ƒm(handle[0])‚©‚çTƒ~ƒm(handle[6])‚Ì“¯‚¶‰æ‘œ‚ğ“–‚Ä‚é
		handle[i] = handle[i - 11];
	}
}