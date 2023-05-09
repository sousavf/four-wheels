#include "Track.h"

const double Track::SIDES_HEIGHT = 0.25;
const double Track::SIDES_WIDTH = 0.5;

/// Cria uma nova pista vazia.
Track::Track()
{
	Init(XYZ(), SIDES_WIDTH, SIDES_HEIGHT);
}



/// Cria uma pista a partir de um ficheiro.
Track::Track(char* filename)
{
	Load(filename);
}



/// Cria uma nova pista vazia com sidesWidth e sidesHeight.
Track::Track(double sidesWidth, double sidesHeight)
{
	Init(XYZ(), sidesWidth, sidesHeight);
}



/// Cria uma nova pista vazia em position.
Track::Track(XYZ position)
{
	Init(position, SIDES_WIDTH, SIDES_HEIGHT);
}



/// Cria uma nova pista vazia em position com sidesWidth e sidesHeight.
Track::Track(XYZ position, double sidesWidth, double sidesHeight)
{
	Init(position, sidesWidth, sidesHeight);
}



/// Cria uma pista a partir de outra.
Track::Track(Track &track)
{
	Init(track.position, track.sidesWidth, track.sidesHeight);
	
	for (int i = 0; i < (int)track.segments.size(); i++)
	{
		this->segments.push_back(new Segment(*(track.segments[i])));
	}
	this->totalLength = track.totalLength;
	this->startOrientation = track.startOrientation;
	this->finishLine = track.finishLine;
	this->space = track.space;
}



/// Cria uma nova pista vazia em position com  sidesWidth e sidesHeight.
void Track::Init(XYZ position, double sidesWidth, double sidesHeight)
{
	this->position = position;
	this->sidesWidth = (sidesWidth > 0) ? sidesWidth : SIDES_WIDTH;
	this->sidesHeight = (sidesHeight > 0) ? sidesHeight : SIDES_HEIGHT;
	this->totalLength = 0;
	this->startOrientation = UNDEFINED_ORIENTATION;
	this->finishLine = NULL;
	this->space = NULL;
}



/// Destrói a pista.
Track::~Track()
{
	for (int i = 0; i < (int)this->segments.size(); i++)
	{
		delete this->segments[i];
	}
}



/// Define a posição da pista (o ponto de partida é a referência).
void Track::SetPosition(XYZ position)
{
	this->position = position;
}



/// Devolve a posição da pista (o ponto de partida é a referência).
XYZ Track::GetPosition() const
{
	return this->position;
}



/// Devolve o número de segmentos.
int Track::GetSegmentsCount() const
{
	return (int)this->segments.size();
}



/// Adiciona um novo segmento à pista (o último segmento é a meta) caso este não invalide
/// a pista e devolve um booleano indicando se conseguiu adicionar o segmento.
bool Track::AddSegment(Segment &segment)
{
	Segment* newSegment = new Segment(segment);

	FixOrientation(*newSegment);

	if (PossibleInconsistency(newSegment->GetOrientation()))
	{
		delete newSegment;
		return false;
	}

	if (this->segments.size() > 0)
	{
		double previousOrientation, orientation, difference;

		previousOrientation = this->segments[(int)this->segments.size() - 1]->GetOrientation();
		orientation = newSegment->GetOrientation();
		difference = (abs(orientation - previousOrientation) <= abs(orientation - (360 + previousOrientation)))
							? orientation - previousOrientation
							: orientation - (360 + previousOrientation);

		if (abs(difference) > 90.0)
		{
			previousOrientation = (int)(previousOrientation + this->startOrientation) % 360;
			orientation = (int)(orientation + this->startOrientation) % 360;
			difference = (abs(orientation - previousOrientation) <= abs(orientation - (360 + previousOrientation)))
							? orientation - previousOrientation
							: orientation - (360 + previousOrientation);
			previousOrientation = previousOrientation + difference * 0.5;

			if (!AddSegment(* (new Segment(newSegment->GetLength() /* 0.5*/, newSegment->GetWidth()
								, previousOrientation))))
			{
				return false;
			}
			//newSegment->SetLength(newSegment->GetLength() * 0.5);
			AddSegment(*newSegment);
			delete newSegment;
		}
		else
		{
			UnsafeAdd(newSegment);
		}
	}
	else
	{
		UnsafeAdd(newSegment);
	}

	return true;
}



/// Adiciona um segmento ao conjunto de segmentos da pista.
void Track::UnsafeAdd(Segment* newSegment)
{
	if (startOrientation == UNDEFINED_ORIENTATION)
	{
		this->startOrientation = newSegment->GetOrientation();
		newSegment->SetOrientation(0);
	}
	this->totalLength += newSegment->GetLength();
	this->segments.push_back(newSegment);
}



/// Corrige a orientação de um segmento para ficar em relação à orientação de início e
/// converte a orientação para ficar entre os valores 0 e 360.
void Track::FixOrientation(Segment &segment) const
{
	// corrige a orientação para estar de acordo com a orientação da pista.
	if (startOrientation != UNDEFINED_ORIENTATION)
	{
		segment.SetOrientation(segment.GetOrientation() - this->startOrientation);
	}

	// converte ângulo para -360 a 360
	segment.SetOrientation((int)segment.GetOrientation() % 360);
	
	// converte ângulo para 0 a 360
	if (segment.GetOrientation() < 0)
	{
		segment.SetOrientation(segment.GetOrientation() + 360.0);
	}
}



/// Dado uma orientação para um possível novo segmento a acrescentar à pista
/// indica se poderá cria uma possível inconsistência na pista (uma intersecção).
bool Track::PossibleInconsistency(double newOrientation)
{
	double orientation, previousOrientation, sum = 0;

	for (int i = (int)this->segments.size(); i > 0; i--)
	{
		orientation = (i == (int)this->segments.size()) ? newOrientation
														: this->segments[i]->GetOrientation();
		previousOrientation = this->segments[i - 1]->GetOrientation();

		if (abs(orientation - previousOrientation) <= abs(orientation - (360 + previousOrientation)))
		{
            sum += orientation - previousOrientation;
		}
		else
		{
			sum += orientation - (360 + previousOrientation);
		}

		if ( sum > 180 || sum < - 180 )
		{
			return true;
		}
	}

	return false;
}



/// Adiciona um novo segmento à pista (o último segmento é a meta) com orientation.
bool Track::AddSegment(double orientation)
{
	return AddSegment(Segment(orientation));
}



/// Constrói a pista no mundo específico.
void Track::Make(World &world)
{
	Space* trackSpace;
	XYZ position;

	this->segmentsPositions.clear();
	trackSpace = new Space(*(world.WorldSpace()));
	position.SetXYZ(this->position);

	for (int i = 0; i < (int) this->segments.size(); i++)
	{
		MakeSides(*(this->segments[i]), position, trackSpace);

		if (i == 0)
		{
			MakeStartOrFinishLine(*(this->segments[i]), position, trackSpace, true);
		}

		if (i + 1 < (int) this->segments.size())
		{
			position = MakeConnectionSegment(*(this->segments[i]), *(this->segments[i + 1])
												, position, trackSpace);
		}
		else
		{
			MakeStartOrFinishLine(*(this->segments[i]), position, trackSpace, false);
		}
	}
	this->space = trackSpace;
	world.AddSpace(*trackSpace);
}



/// Dado um segmento cria os lados correspondentes.
void Track::MakeSides(Segment segment, XYZ position, Space* trackSpace)
{
	Line::Point firstPoint, secondPoint;
	XYZ rotation;

	rotation.SetXYZ(0, 0, segment.GetOrientation());
	firstPoint = GetFirstPoint(segment);
	secondPoint = GetSecondPoint(segment);
	MakeSide(position, firstPoint, rotation, segment.GetLength(), trackSpace);
	MakeSide(position, secondPoint, rotation, segment.GetLength(), trackSpace);
	this->segmentsPositions.push_back(XYZ(position.x, position.y, rotation.z));
}



/// Cria um segmento de ligação entre dois segmentos.
XYZ Track::MakeConnectionSegment(Segment segment1, Segment segment2, XYZ position, Space* trackSpace)
{
	Line line1, line2;
	Line::Point firstPoint, secondPoint, nextFirstPoint, nextSecondPoint;
	XYZ nextPosition, position1, position2;
	double orientation, length, nextOrientation, nextLength;

	orientation = Math::ToRadians(segment1.GetOrientation());
	length = segment1.GetLength();
	nextOrientation = Math::ToRadians(segment2.GetOrientation());
	nextLength = segment2.GetLength();

	firstPoint = GetFirstPoint(segment1);
	secondPoint = GetSecondPoint(segment1);

	nextPosition.SetXYZ(position);
	nextPosition.x += 1.5 * (length * sin(orientation) + nextLength * sin(nextOrientation)) * -1;
	nextPosition.y += 1.5 * (length * cos(orientation) + nextLength * cos(nextOrientation));
	nextFirstPoint = GetFirstPoint(segment2);
	nextSecondPoint = GetSecondPoint(segment2);

	line1 = MakeConnectionLine(position, firstPoint, segment1, nextPosition, nextFirstPoint, segment2);
	line2 = MakeConnectionLine(position, secondPoint, segment1, nextPosition, nextSecondPoint, segment2);

	if (line1.Intersects(line2))
	{
		position1 = MakeSide(line1.GetP1(), line2.GetP2(), trackSpace);
		position2 = MakeSide(line2.GetP1(), line1.GetP2(), trackSpace);
	}
	else
	{
		position1 = MakeSide(line1.GetP1(), line1.GetP2(), trackSpace);
		position2 = MakeSide(line2.GetP1(), line2.GetP2(), trackSpace);
	}
	this->segmentsPositions.push_back(XYZ(abs(position1.x - position2.x) * 0.5
											+ Math::Min(position1.x, position2.x)
									, abs(position1.y - position2.y) * 0.5
											+ Math::Min(position1.y, position2.y)
									, (segment1.GetOrientation() + segment2.GetOrientation()) * 0.5));
	
	return nextPosition;
}



/// Dado um segmento constrói a meta final ou fecha o segmento inicial
/// mediante o valor do o booleano start.
void Track::MakeStartOrFinishLine(Segment segment, XYZ position, Space* trackSpace, bool start)
{
	BoxGeometry* box;
	Line::Point p1, p2;
	double orientation, length, x1, y1, x2, y2, xm, ym, angle;

	orientation = Math::ToRadians(segment.GetOrientation());
	length = segment.GetLength();

	p1 = GetFirstPoint(segment);
	p2 = GetSecondPoint(segment);
	p1.SetXY(p1.GetX() + position.x, p1.GetY() + position.y);
	p2.SetXY(p2.GetX() + position.x, p2.GetY() + position.y);

	if (start)
	{
		p1 = GetBeginPoint(p1, segment);
		p2 = GetBeginPoint(p2, segment);
	}
	else
	{
		p1 = GetEndPoint(p1, segment);
		p2 = GetEndPoint(p2, segment);
	}

	x1 = p1.GetX();
	y1 = p1.GetY();
	x2 = p2.GetX();
	y2 = p2.GetY();

	length = sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
	xm = x1 + (x2 - x1) / 2;
	ym = y1 + (y2 - y1) / 2;
	angle = Math::PI * 1.5 + acos(abs(x2 - x1) / length) * ( x2 < x1 ? -1 : 1)
											* ( y2 < y1 ? -1 : 1);
	angle = Math::ToDegrees(angle);

	box = new BoxGeometry(*trackSpace, this->sidesWidth, this->sidesHeight
								, segment.GetWidth() - this->sidesWidth
								, (!start) ? FINISH_LINE_COLOR : START_LINE_COLOR);
	box->SetPosition(XYZ(xm, ym, this->position.z));
	box->SetRotation(XYZ(0, 0, angle));
	trackSpace->AddGeometry(*box);

	if (!start)
	{
		this->finishLine = box;
	}
}



/// Devolve um ponto com as coordenadas da 1ª posição do lado da pista.
Line::Point Track::GetFirstPoint(Segment segment) const
{
	double x, y, orientation;

	orientation = Math::ToRadians(segment.GetOrientation());
	x = (segment.GetWidth() / 2) * sin(Math::PI * 0.5 - orientation);
	y = (segment.GetWidth() / 2) * cos(Math::PI * 0.5 - orientation);

	return Line::Point(x, y);
}



/// Devolve um ponto com as coordenadas da 2ª posição do lado da pista.
Line::Point Track::GetSecondPoint(Segment segment) const
{
	double x, y, orientation;

	orientation = Math::ToRadians(segment.GetOrientation());
	x = - (segment.GetWidth() / 2) * sin(Math::PI * 0.5 - orientation);
	y = - (segment.GetWidth() / 2) * cos(Math::PI * 0.5 - orientation);

	return Line::Point(x, y);
}



/// Cria um lado da pista na posição com rotação e length específicos.
/// Adiciona o lado a trackSpace.
void Track::MakeSide(XYZ position, Line::Point point, XYZ rotation, double length, Space* trackSpace) const
{
	BoxGeometry* box;
	XYZ absPosition(position);

	absPosition.x = position.x + point.GetX();
	absPosition.y = position.y + point.GetY();
	box = new BoxGeometry(*trackSpace, this->sidesWidth, this->sidesHeight, length, SIDES_COLOR);
	box->SetPosition(absPosition);
	box->SetRotation(rotation);
	trackSpace->AddGeometry(*box);
}



/// Cria um lado de point1 a point2 e coloca-o em trackSpace. Devolve a posição do centro do lado.
XYZ Track::MakeSide(Line::Point point1, Line::Point point2, Space* trackSpace) const
{
	BoxGeometry* box;
	XYZ position;
	double length, width, height, angle;

	width = abs(point2.GetX() - point1.GetX());
	height = abs(point2.GetY() - point1.GetY());
	length = sqrt(width * width + height * height);
	angle = Math::PI * 0.5 + acos(width / length) * ( point2.GetX() < point1.GetX() ? -1 : 1)
											* ( point2.GetY() < point1.GetY() ? -1 : 1);
	angle = Math::ToDegrees(angle);
	position.x = Math::Min(point1.GetX(), point2.GetX()) + width * 0.5;
	position.y = Math::Min(point1.GetY(), point2.GetY()) + height * 0.5;
	position.z = this->position.z;

	box = new BoxGeometry(*trackSpace, this->sidesWidth, this->sidesHeight, length, SIDES_COLOR);
	box->SetPosition(position);
	box->SetRotation(XYZ(0, 0, angle));
	trackSpace->AddGeometry(*box);

	return position;
}



/// Devolve o ponto final de um segmento.
Line::Point Track::GetEndPoint(Line::Point point, Segment segment) const
{
	Line::Point endPoint;
	double orientation;

	orientation = Math::ToRadians(segment.GetOrientation());
	endPoint.SetX(point.GetX() + segment.GetLength() * 0.5 * sin(orientation) * -1);
	endPoint.SetY(point.GetY() + segment.GetLength() * 0.5 * cos(orientation));

	return endPoint;
}



/// Devolve o ponto inicial de um segmento.
Line::Point Track::GetBeginPoint(Line::Point point, Segment segment) const
{
	Line::Point beginPoint;
	double orientation;

	orientation = Math::ToRadians(segment.GetOrientation());
	beginPoint.SetX(point.GetX() - segment.GetLength() * 0.5 * sin(orientation) * -1);
	beginPoint.SetY(point.GetY() - segment.GetLength() * 0.5 * cos(orientation));

	return beginPoint;
}
		
		

/// Cria uma linha de ligação entre os segmentos.
Line Track::MakeConnectionLine(XYZ position, Line::Point point, Segment segment
						, XYZ nextPosition, Line::Point nextPoint, Segment nextSegment) const
{
	Line::Point p1, p2;

	p1 = GetEndPoint(point, segment);
	p2 = GetBeginPoint(nextPoint, nextSegment);
	p1.SetXY(p1.GetX() + position.x, p1.GetY() + position.y);
	p2.SetXY(p2.GetX() + nextPosition.x, p2.GetY() + nextPosition.y);

	return Line(p1, p2);
}



/// Define a altura dos limites.
void Track::SetSidesHeight(double newHeight)
{
	if (newHeight > 0)
	{
		this->sidesHeight = newHeight;
	}
}



/// Indica a altura dos limites.
double Track::GetSidesHeight() const
{
	return this->sidesHeight;
}



/// Define a largura dos limites.
void Track::SetSidesWidth(double newWidth)
{
	if (newWidth > 0)
	{
		this->sidesWidth = newWidth;
	}
}



/// Indica a largura dos limites
double Track::GetSidesWidth() const
{
	return this->sidesWidth;
}



/// Limpa a pista e cria uma nova ao acaso com comprimento length.
void Track::Random(double length)
{
	Segment* segment;
	double previousOrientation = 0;

	this->segments.clear();

	while (this->totalLength < length)
	{
		segment = Segment::Random(previousOrientation);
		
		if (this->totalLength + segment->GetLength() > length)
		{
			segment->SetLength(segment->GetLength() - this->totalLength);
		}

        if (AddSegment(*segment))
		{
			previousOrientation = segment->GetOrientation();
		}
	}
	segment->~Segment();
	delete segment;
}



/// Adiciona segmentos ao acaso até a pista ter segments segmentos.
void Track::Random(int segments)
{
	Segment* segment;
	double previousOrientation;
	
	previousOrientation = (this->segments.size() > 0)
							? this->segments[this->segments.size() - 1]->GetOrientation()
							: 0;

	while ((int)this->segments.size() < segments)
	{
		segment = Segment::Random(previousOrientation);
		
        if (AddSegment(*segment))
		{
			previousOrientation = segment->GetOrientation();
		}
	}
	segment->~Segment();
	delete segment;
}



/// Carrega uma pista dum ficheiro.
void Track::Load(char* filename)
{
	this->segments.clear();
	std::ifstream ifile(filename);
	ifile >> *this;
	ifile.close();
}



/// Grava a pista para um ficheiro.
void Track::Save(char* filename)
{
	std::ofstream ofile(filename);
	ofile << *this;
	ofile.close();
}



/// Escreve uma pista para um output stream.
std::ostream& operator << (std::ostream &os, const Track &track)
{
	XYZ position = track.GetPosition();

	os << position << ":" << track.GetSidesWidth() << ":" << track.GetSidesHeight()
		<< ":" << (int)track.segments.size() << "|";

	for (int i = 0; i < (int) track.segments.size(); i++)
	{
		os << *(track.segments[i]);
	}

	return os;
}



/// Lê uma pista de um output stream.
std::istream& operator >> (std::istream &is, Track &track)
{
	Track::Segment newSegment;
	XYZ position;
	double width, height, segments;
	char c;

	is >> position >> c >> width >> c >> height >> c >> segments >> c;
	track.SetPosition(position);
	track.SetSidesWidth(width);
	track.SetSidesHeight(height);
	track.segments.clear();

	for (int i = 0; i < segments; i++)
	{
		if (is >> newSegment)
		{
			track.segments.push_back(new Track::Segment(newSegment));
		}
	}

	return is;
}



/// Devolve o comprimento total da pista.
double Track::GetTotalLength() const
{
	return this->totalLength;
}



/// Devolve o espaço da pista.
Space* Track::GetSpace() const
{
	return this->space;
}



/// Devolve a geometria correspondente à meta.
BoxGeometry* Track::FinishLine() const
{
	return this->finishLine;
}



/// Devolve um vector com as posições em X e Y (x, y) dos segmentos e as suas orientações (z).
std::vector< XYZ > Track::GetSegmentsPositions() const
{
	return this->segmentsPositions;
}



/// Devolve os segmentos que constituem a pista.
std::vector< Track::Segment* > Track::GetSegments() const
{
	return this->segments;
}