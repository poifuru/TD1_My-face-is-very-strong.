//<>�w�b�_�[�t�@�C��
#include <Novice.h>

//""�w�b�_�[�t�@�C��
#include "struct.h"
#include "player.h"

const char kWindowTitle[] = "LC1A_25_�}�X��_�S�E_�^�C�g��";

//�R�����g�G���A
/**/

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ���C�u�����̏�����
	Novice::Initialize(kWindowTitle, 1920, 1080);
	Novice::SetWindowMode(kFullscreen);

	//�L�[���͂��󂯎�锠
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player* player = new Player();

	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		// �t���[���̊J�n
		Novice::BeginFrame();

		// �L�[���͂��󂯎��
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ���X�V������������
		///

		player->Update(keys, preKeys);

		///
		/// ���X�V���������܂�
		///

		///
		/// ���`�揈����������
		///

		//�n��
		Novice::DrawLine(0, 900, 1920, 900, BLACK);

		player->Draw();
		
		///
		/// ���`�揈�������܂�
		///

		// �t���[���̏I��
		Novice::EndFrame();

		// ESC�L�[�������ꂽ�烋�[�v�𔲂���
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ���C�u�����̏I��
	Novice::Finalize();
	return 0;
}
