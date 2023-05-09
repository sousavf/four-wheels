#ifndef Track_h
#define Track_h

#include "Line.h"
#include "World.h"

class Track
{
	public:
		struct Segment
		{
			protected:
				double length;
				double width;
				double orientation;

			public:
				static const int DEFAULT_WIDTH = 10;
				static const int DEFAULT_LENGTH = 10;
				static const int MIN_WIDTH = 4;
				static const int MIN_LENGTH = 3;
				static const int MAX_WIDTH = 25;
				static const int MAX_LENGTH = 10;

				Segment()
				{
					this->length = DEFAULT_LENGTH;
					this->width = DEFAULT_WIDTH;
					this->orientation = 0;
				}

				Segment(Segment &segment)
				{
					this->length = segment.length;
					this->width = segment.width;
					this->orientation = segment.orientation;
				}

				Segment(double length, double orientation)
				{
					SetLength(length);
					this->width = DEFAULT_WIDTH;
					this->orientation = orientation;
				}

				Segment(double length, double width, double orientation)
				{
					SetLength(length);
					SetWidth(width);
					this->orientation = orientation;
				}

				Segment(double orientation)
				{
					this->length = DEFAULT_LENGTH;
					this->width = DEFAULT_WIDTH;
					this->orientation = orientation;
				}

				static Segment* Random(double previousOrientation)
				{
					double orientation = Math::RandomDouble(previousOrientation
															, previousOrientation + 360.0);
					orientation = (int)orientation % 360;

					return new Segment(
							Math::RandomDouble(Segment::MIN_LENGTH, Segment::MAX_LENGTH)
							, Math::RandomDouble(Segment::MIN_WIDTH, Segment::MAX_WIDTH)
							, orientation);
				}

				double GetWidth()
				{
					return this->width;
				}

				double GetLength()
				{
					return this->length;
				}

				double GetOrientation()
				{
					return this->orientation;
				}

				void SetWidth(double width)
				{
					if (width < MIN_WIDTH)
					{
						this->width = MIN_WIDTH;
					}
					else if (width > MAX_WIDTH)
					{
						this->width = MAX_WIDTH;
					}
					else
					{
						this->width = width;
					}
				}

				void SetLength(double length)
				{
					if (length < MIN_LENGTH)
					{
						this->length = MIN_LENGTH;
					}
					else if (length > MAX_LENGTH)
					{
						this->length = MAX_LENGTH;
					}
					else
					{
						this->length = length;
					}
				}

				void SetOrientation(double orientation)
				{
					this->orientation = orientation;
				}

				friend std::ostream& operator << (std::ostream &os, Segment &segment)
				{
					os << segment.GetLength() << ":" << segment.GetWidth() << ":"
							<< segment.GetOrientation() << ";";

					return os;
				}

				friend std::istream& operator >> (std::istream &is, Segment &segment)
				{
					double length, width, orientation;
					char c;

					is >> length >> c >> width >> c >> orientation >> c;
					segment.SetLength(length);
					segment.SetWidth(width);
					segment.SetOrientation(orientation);

					return is;
				}
		};

		const static double SIDES_HEIGHT;
		const static double SIDES_WIDTH;

		Track();
		Track(char* filename);
		Track(double sidesWidth, double sidesHeight);
		Track(XYZ position);
		Track(XYZ position, double sidesWidth, double sidesHeight);
		Track(Track &track);
		~Track();

		void SetPosition(XYZ position);
		XYZ GetPosition() const;
		bool AddSegment(Segment &segment);
		bool AddSegment(double orientation);
		void Make(World &world);
		void SetSidesHeight(double newHeight);
		double GetSidesHeight() const;
		void SetSidesWidth(double newWidth);
		double GetSidesWidth() const;
		void Random(double length);
		void Random(int segments);
		void Load(char* filename);
		void Save(char* filename);
		double GetTotalLength() const;
		BoxGeometry* FinishLine() const;
		Space* GetSpace() const;
		std::vector< XYZ > GetSegmentsPositions() const;
		std::vector< Segment* > GetSegments() const;
		int GetSegmentsCount() const;

		friend std::ostream& operator << (std::ostream &os, const Track &track);
		friend std::istream& operator >> (std::istream &is, Track &track);

	protected:
		const static Geometry::Color SIDES_COLOR = Geometry::Color::Gray;
		const static Geometry::Color FINISH_LINE_COLOR = Geometry::Color::White;
		const static Geometry::Color START_LINE_COLOR = Geometry::Color::Red;
		const static int UNDEFINED_ORIENTATION = 999;

		std::vector< Segment* > segments;
		std::vector< XYZ > segmentsPositions;
		XYZ position;
		double sidesHeight;
		double sidesWidth;
		double totalLength;
		double startOrientation;
		BoxGeometry* finishLine;
		Space* space;

		void Init(XYZ position, double sidesWidth, double sidesHeight);
		Line::Point GetFirstPoint(Segment segment) const;
		Line::Point GetSecondPoint(Segment segment) const;
		Line::Point GetEndPoint(Line::Point point, Segment segment) const;
		Line::Point GetBeginPoint(Line::Point point, Segment segment) const;
		void MakeSide(XYZ position, Line::Point point, XYZ rotation, double length, Space* trackSpace) const;
		XYZ MakeSide(Line::Point point1, Line::Point point2, Space* trackSpace) const;
		Line MakeConnectionLine(XYZ position, Line::Point point, Segment segment
								, XYZ nextPosition, Line::Point nextPoint, Segment nextSegment) const;
		XYZ MakeConnectionSegment(Segment segment1, Segment segment2, XYZ position, Space* trackSpace);
		void MakeSides(Segment segment, XYZ position, Space* trackSpace);
		void MakeStartOrFinishLine(Segment segment, XYZ position, Space* trackSpace, bool start);
		bool PossibleInconsistency(double newOrientation);
		void FixOrientation(Segment &segment) const;
		void UnsafeAdd(Segment* segment);
};


#endif