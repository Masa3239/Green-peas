BetterInput v3.0

使い方
1. アクションを追加する

	1.1 - ../System/Input/Literal/InputActions.h 内の Input::Action に任意の名前を追加してアクションIDを作成する

	1.2 - ../System/InputManager.cppに移動する
	
	1.3 - bool InputManager::Initialize()関数の定義に移動する

	1.4 - アクションデータの初期化の下に Bind()関数を書く

	1.5 - 引数には Bind(Input::Action::アクションID, Input::Device::入力デバイス, KeyCode::Button::キーコード,
		モディファイア（任意、詳しくは5で）, ゲームパッドの識別番号（任意、現在使用不可）) を渡す

		例：
		Bind(Input::Action::Attack, Input::Device::Keyboard, KeyCode::Button::Space);

		例（モディファイア付）：
		Bind(Input::Action::Move, Input::Device::Keyboard, KeyCode::Button::W,
		{
			std::make_shared<InputModifierNegate>(true, true),
			std::make_shared<InputModifierSwizzleAxis>()
		});

	1.6 - 完了

2. 押下状態を取得する

	2.1 - InputManager::GetInstance()でインスタンスを取得して任意の入力方法を選ぶ
		IsDown -> 押されているかどうか
		IsPressed -> 押された瞬間かどうか
		IsReleased -> 離された瞬間かどうか
		IsHeld -> 一定フレーム数押されているか、離されているかどうか

	2.2 - 結果をboolで取得

3. アナログ値を取得する

	3.1 - GetAs〇〇()関数でアナログ値を取得できる
		GetAsFloat() -> floatで取得
		GetAsVector2() -> Vector2で取得

4. 入力デバイスから直接押下状態を取得する

	4.1 - ../System/Input/ の入力デバイスをインクルードしてIsDown関数で押下状態を取得できる

	4.2 - 種類
		Keyboard.h -> キーボード
		Mouse.h -> マウス
		Gamepad.h -> ゲームパッド

5. モディファイアについて

	4.1 - 値を加工することができる
		InputModifierNegate(bool x, bool y) -> 適用する成分を指定して値を反転させる
		InputModifierSwizzleAxis() -> YとX成分を入れ替える
		InputModifierDeadzone(float dzMin, float dzMax) -> デッドゾーンを適用する範囲を指定する（値がdzMin以下のとき0、dzMax以上のとき1）

	4.2 - 活用方法
		WASDをVector2として取得できるようにできる
		W -> Negate + Swizzle = 上
		S -> Swizzle = 下
		A -> Negate = 左
		D -> なし = 右

	4.3 - 適用方法
		../System/Input/Modifier/InputModifer〇〇

		InputManagerでBind関数を呼ぶときに引数のstd::vector<IInputDeviceModifier>の部分に{}で囲って
		std::shared_ptrのモディファイアを入れたらそのバインドに適用することができる