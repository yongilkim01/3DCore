#pragma once
// FVector�� �����ϰڽ��ϴ�.
// FVector xy
// FVector3D xyz
// FVector4D xyzw
// FVector4D == FVector;

// #include <DirectXMath.h>


class UEngineMath
{
public:
	// ��� ����
	static const double DPI;
	static const double DPI2;

	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	static float Sqrt(float _Value)
	{
		return ::sqrtf(_Value);
	}

	template <typename DataType>
	DataType ClampMax(DataType value, DataType maxValue)
	{
		return (value > maxValue) ? maxValue : value;
	}

	template <typename DataType>
	DataType ClampMin(DataType value, DataType minValue)
	{
		return (value < minValue) ? minValue : value;
	}

	template <typename DataType>
	static DataType Clamp(DataType value, DataType minValue, DataType maxValue)
	{
		if (value < minValue)
			return minValue;
		else if (value > maxValue)
			return maxValue;
		else
			return value;
	}

	template <typename DataType>
	static DataType Lerp(DataType A, DataType B, DataType Alpha)
	{
		return A * (1 - Alpha) + B * Alpha;
	}
};

class FVector
{
public:
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 0.0f;

	static const FVector ZERO;
	static const FVector LEFT;
	static const FVector RIGHT;
	static const FVector UP;
	static const FVector DOWN;

	FVector()
	{

	}

	FVector(float _X, float _Y) : X(_X), Y(_Y)
	{

	}

	FVector(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}


	FVector(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}

	FVector(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y))
	{

	}


	static FVector Normalize(FVector _Value)
	{
		_Value.Normalize();
		return _Value;
	}

	// 360�� �������� �־����.
	static FVector AngleToVectorDeg(float _Angle)
	{
		// 360�й��� => �������� �ٲٴ� ���� ������ �Ѵ�.
		// 360 => 6.28

		// ���� ����ü�踦 ������� sinf(_Angle) cosf

		// �ٺ��Լ��� ���� �������� �����
		return AngleToVectorRad(_Angle * UEngineMath::D2R);
	}


	static FVector Lerp(FVector _A, FVector _B, float _Alpha)
	{
		FVector Result;
		_Alpha = UEngineMath::Clamp(_Alpha, 0.0f, 1.0f);
		Result.X = UEngineMath::Lerp(_A.X, _B.X, _Alpha);
		Result.Y = UEngineMath::Lerp(_A.Y, _B.Y, _Alpha);
		return Result;
	}

	//          Rad ������ �־��ָ� 
	// ���⿡�� ���� ������� �������ټ� �ִ°�
	// ���̰� 1�� �����̴�.
	// static�Դϱ�?
	static FVector AngleToVectorRad(float _Angle)
	{
		// Ư�� ������ ����Ű�� ���͸� ����� �ִٰ� ����?
		// ���� ���̿� ������ �����ض�.
		// ������ �������µ� ���̴� 1�� ���͸� ������ �̴ϴ�.

		// 0���϶��� �غ�      0���ϴ��� ����

		// cosf(_Angle) = �غ�
		return { cosf(_Angle), sinf(_Angle) };
	}


	int iX() const
	{
		return static_cast<int>(X);
	}

	int iY() const
	{
		return static_cast<int>(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	// X�� Y�� 0�������� ��Ʈ���� �Լ�.
	bool IsZeroed() const
	{
		return X == 0.0f || Y == 0.0f;
	}

	FVector Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}

	// ������ �����Դϴ�.
	float Length() const
	{
		return UEngineMath::Sqrt(X * X + Y * Y);
	}

	POINT ConvertWindowPOINT()
	{
		return { iX(), iY() };
	}

	class FIntPoint ConvertToPoint() const;

	void Normalize()
	{
		float Len = Length();
		if (0.0f < Len && false == isnan(Len))
		{
			X = X / Len;
			Y = Y / Len;
		}
		return;
	}

	// 
	void RotationXDeg(float _Angle)
	{
		RotationXRad(_Angle * UEngineMath::D2R);
	}

	void RotationXRad(float _Angle)
	{
		FVector Copy = *this;
		Z = (Copy.Z * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
		Y = (Copy.Z * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	}

	FVector RotationXDegReturn(float _Angle)
	{
		return RotationXRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationXRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.Z = (Z * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (Z * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}


	// 
	void RotationYDeg(float _Angle)
	{
		RotationYRad(_Angle * UEngineMath::D2R);
	}

	void RotationYRad(float _Angle)
	{
		FVector Copy = *this;
		X = (Copy.X * cosf(_Angle)) - (Copy.Z * sinf(_Angle));
		Z = (Copy.X * sinf(_Angle)) + (Copy.Z * cosf(_Angle));
	}

	FVector RotationYDegReturn(float _Angle)
	{
		return RotationYRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationYRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.X = (X * cosf(_Angle)) - (Z * sinf(_Angle));
		Result.Z = (X * sinf(_Angle)) + (Z * cosf(_Angle));
		return Result;
	}

	// 
	void RotationZDeg(float _Angle)
	{
		RotationZRad(_Angle * UEngineMath::D2R);
	}

	void RotationZRad(float _Angle)
	{
		FVector Copy = *this;
		X = (Copy.X * cosf(_Angle)) - (Copy.Y * sinf(_Angle));
		Y = (Copy.X * sinf(_Angle)) + (Copy.Y * cosf(_Angle));
	}

	FVector RotationZDegReturn(float _Angle)
	{
		return RotationZRadReturn(_Angle * UEngineMath::D2R);
	}

	FVector RotationZRadReturn(float _Angle)
	{
		FVector Result = *this;
		Result.X = (X * cosf(_Angle)) - (Y * sinf(_Angle));
		Result.Y = (X * sinf(_Angle)) + (Y * cosf(_Angle));
		return Result;
	}

	float Dot(const FVector& other) const
	{
		return X * other.X + Y * other.Y;
	}

	FVector operator*(float _Value) const
	{
		FVector Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		return Result;
	}

	FVector operator+(const FVector& _Other) const
	{
		FVector Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector& operator-=(const FVector& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}


	FVector operator-(const FVector& _Other) const
	{
		FVector Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FVector operator-() const
	{
		FVector Result;
		Result.X = -X;
		Result.Y = -Y;
		return Result;
	}

	FVector operator/(int _Value) const
	{
		FVector Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}

	FVector operator/(const FVector& Other) const
	{
		FVector Result;
		Result.X = X / Other.X;
		Result.Y = Y / Other.Y;
		return Result;
	}

	// ture�� ������ 
	bool operator==(const FVector& _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	// float�� �񱳰� ������ ����
	// const�� ���� �Լ������� const�� ���� �Լ� ȣ���Ҽ� ����.
	bool EqualToInt(FVector _Other) const
	{
		// const FVector* const Ptr;
		// this = nullptr;
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

	//bool Compare(FVector _Other, float _limite = 0.0f) const
	//{
	//	return X == _Other.X && Y == _Other.Y;
	//}

	FVector& operator+=(const FVector& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	FVector& operator*=(const FVector& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		return *this;
	}

	FVector& operator*=(float _Other)
	{
		X *= _Other;
		Y *= _Other;
		return *this;
	}


	std::string ToString()
	{
		std::string Stream;

		Stream += "X : [";
		Stream += std::to_string(X);
		Stream += "] Y : [";
		Stream += std::to_string(Y);
		Stream += "]";
		return Stream;
	}

};

enum class ECollisionType
{
	Point,
	Rect,
	CirCle, // Ÿ���� �ƴ� ����� 
	Max

	//AABB,
	//OBB,
};

// ��κ� ������Ʈ���� ũ��� ��ġ�� �ѽ��Դϴ�.
// �׷��� �� 2������ ��� ���� �ڷ����� ���� �װ� ���.
class FTransform
{
private:
	friend class CollisionFunctionInit;

	static std::function<bool(const FTransform&, const FTransform&)> AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

public:
	static bool Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right);

	// ������ ���� ���� �Լ���?
	static bool PointToCirCle(const FTransform& _Left, const FTransform& _Right);
	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);

	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToCirCle(const FTransform& _Left, const FTransform& _Right);

	static bool CirCleToCirCle(const FTransform& _Left, const FTransform& _Right);
	static bool CirCleToRect(const FTransform& _Left, const FTransform& _Right);


	FVector Scale;
	FVector Location;


	FVector CenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	FVector CenterLeftBottom() const
	{
		FVector Result;
		Result.X = Location.X - Scale.hX();
		Result.Y = Location.Y + Scale.hY();
		return Result;
	}

	float CenterLeft() const
	{
		return Location.X - Scale.hX();
	}

	float CenterTop() const
	{
		return Location.Y - Scale.hY();
	}

	FVector CenterRightTop() const
	{
		FVector Result;
		Result.X = Location.X + Scale.hX();
		Result.Y = Location.Y - Scale.hY();
		return Result;
	}

	FVector CenterRightBottom() const
	{
		return Location + Scale.Half();
	}

	float CenterRight() const
	{
		return Location.X + Scale.hX();
	}

	float CenterBottom() const
	{
		return Location.Y + Scale.hY();
	}
};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}

	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}


	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}


};


class UColor
{
public:
	static const UColor WHITE;
	static const UColor BLACK;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	bool operator==(const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}


	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};

using float4 = FVector;