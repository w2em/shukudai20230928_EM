# include <Siv3D.hpp>

bool clicked = false;
int block = 0;
int life = 5;
double speed = 90.0;

void Main()
{
	// フォント変数を宣言してサイズとスタイルを指定
	Font font(60, Typeface::Bold);

	// ブロックのサイズ
	constexpr Size brickSize{ 40, 20 };

	// ボールの速度
	Vec2 ball01Velocity{ speed, -speed * 3 };

	// ボールの速度
	Vec2 ball02Velocity{ -speed, -speed * 2 };

	// ボールの速度
	Vec2 ball03Velocity{ -speed, -speed };

	// ボール
	Circle ball01{ 400, 400, 8 };

	// ボール
	Circle ball02{ 400, 400, 8 };

	// ボール
	Circle ball03{ 400, 400, 8 };

	// ブロックの配列
	Array<Rect> bricks;

	// 横 (Scene::Width() / blockSize.x) 個、縦 10 個のブロックを配列に追加する
	for (auto p : step(Size{ (Scene::Width() / brickSize.x), 10 }))
	{
		bricks << Rect{ (p.x * brickSize.x), (60 + p.y * brickSize.y), brickSize };
	}

	while (System::Update())
	{
		// パドル
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 150, 10 };

		if (MouseL.down() || MouseR.down())
		{
			clicked = true;
		}

		if (clicked)
		{
			// ボールを移動
			ball01.moveBy(ball01Velocity * Scene::DeltaTime());
			ball02.moveBy(ball02Velocity * Scene::DeltaTime());
			ball03.moveBy(ball03Velocity * Scene::DeltaTime());
		}

		// ブロックを順にチェック
		for (auto it = bricks.begin(); it != bricks.end(); ++it)
		{
			// ブロックとボールが交差していたら
			if (it->intersects(ball01))
			{
				// ボールの向きを反転する
				(it->bottom().intersects(ball01) || it->top().intersects(ball01)
					? ball01Velocity.y : ball01Velocity.x) *= -1;

				// ブロックを配列から削除（イテレータが無効になるので注意）
				bricks.erase(it);

				speed = speed + 0.5;

				block++;
				// これ以上チェックしない
				break;
			}

			if (it->intersects(ball02))
			{
				// ボールの向きを反転する
				(it->bottom().intersects(ball02) || it->top().intersects(ball02)
					? ball02Velocity.y : ball02Velocity.x) *= -1;

				// ブロックを配列から削除（イテレータが無効になるので注意）
				bricks.erase(it);

				speed = speed + 0.5;

				block++;
				// これ以上チェックしない
				break;
			}

			if (it->intersects(ball03))
			{
				// ボールの向きを反転する
				(it->bottom().intersects(ball03) || it->top().intersects(ball03)
					? ball03Velocity.y : ball03Velocity.x) *= -1;

				// ブロックを配列から削除（イテレータが無効になるので注意）
				bricks.erase(it);

				speed = speed + 0.5;

				block++;
				// これ以上チェックしない
				break;
			}
		}

		// 天井にぶつかったらはね返る
		if (ball01.y < 0 && ball01Velocity.y < 0)
		{
			speed = speed + 0.5;

			ball01Velocity.y *= -1;
		}

		// 天井にぶつかったらはね返る
		if (ball02.y < 0 && ball02Velocity.y < 0)
		{
			speed = speed + 0.5;

			ball02Velocity.y *= -1;
		}

		// 天井にぶつかったらはね返る
		if (ball03.y < 0 && ball03Velocity.y < 0)
		{
			speed = speed + 0.5;

			ball03Velocity.y *= -1;
		}

		// 左右の壁にぶつかったらはね返る
		if ((ball01.x < 0 && ball01Velocity.x < 0)
			|| (Scene::Width() < ball01.x && 0 < ball01Velocity.x))
		{
			speed = speed + 0.5;

			ball01Velocity.x *= -1;
		}

		// 左右の壁にぶつかったらはね返る
		if ((ball02.x < 0 && ball02Velocity.x < 0)
			|| (Scene::Width() < ball02.x && 0 < ball02Velocity.x))
		{
			speed = speed + 0.5;

			ball02Velocity.x *= -1;
		}

		// 左右の壁にぶつかったらはね返る
		if ((ball03.x < 0 && ball03Velocity.x < 0)
			|| (Scene::Width() < ball03.x && 0 < ball03Velocity.x))
		{
			speed = speed + 0.5;

			ball03Velocity.x *= -1;
		}

		// パドルにあたったらはね返る
		if (0 < ball01Velocity.y && paddle.intersects(ball01))
		{
			speed = speed + 0.5;

			// パドルの中心からの距離に応じてはね返る方向を変える
			ball01Velocity = Vec2{ (ball01.x - paddle.center().x) * 10, -ball01Velocity.y }.setLength(speed);
		}

		// パドルにあたったらはね返る
		if (0 < ball02Velocity.y && paddle.intersects(ball02))
		{
			speed = speed + 0.5;

			// パドルの中心からの距離に応じてはね返る方向を変える
			ball02Velocity = Vec2{ (ball02.x - paddle.center().x) * 10, -ball02Velocity.y }.setLength(speed);
		}

		// パドルにあたったらはね返る
		if (0 < ball03Velocity.y && paddle.intersects(ball03))
		{
			speed = speed + 0.5;

			// パドルの中心からの距離に応じてはね返る方向を変える
			ball03Velocity = Vec2{ (ball03.x - paddle.center().x) * 10, -ball03Velocity.y }.setLength(speed);
		}

		if (ball01.y > 600 && ball01Velocity.y > 0)
		{
			speed = speed + 0.5;

			ball01Velocity.y *= -1;
			life--;
		}

		if (ball02.y > 600 && ball02Velocity.y > 0)
		{
			speed = speed + 0.5;

			ball02Velocity.y *= -1;
			life--;
		}

		if (ball03.y > 600 && ball03Velocity.y > 0)
		{
			speed = speed + 0.5;

			ball03Velocity.y *= -1;
			life--;
		}

		if (block == 200)
		{
			font(U"ゲームクリア").drawAt(Scene::Center(), ColorF{ HSV{ 0, 1, 1 } });
		}

		if (life <= 0) {
			font(U"ゲームオーバー").drawAt(Scene::Center(), ColorF{ HSV{ 0, 1, 1 } });
		}

		// すべてのブロックを描画する
		for (const auto& brick : bricks)
		{
			brick.stretched(-1).draw(HSV{ brick.y - 40 });
		}

		font(U"ライフ: {}"_fmt(life)).drawAt(150, 50);

		// ボールを描く
		ball01.draw();

		// ボールを描く
		ball02.draw();

		// ボールを描く
		ball03.draw();

		// パドルを描く
		paddle.draw();
	}
}
