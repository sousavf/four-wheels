#include "ODEHeaders.h"

using namespace ODE;

/// Cria um novo contacto.
ODEContact::ODEContact()
{
}



/// Cria um contacto a partir de um dContact.
ODEContact::ODEContact(dContact contact)
{
	this->contact = contact;
	this->contact.surface.mode = 0;
}



/// Destrói o contacto.
ODEContact::~ODEContact()
{
}



/// "Esvazia" o surface mode.
void ODEContact::cleanSurface()
{
	this->contact.surface.mode = 0;
}



/// Se usado, representa a direcção de fricção 1, senão é calculado automaticamente
/// como se fosse prependicular à normal do contacto (orientação imprevisível).
void ODEContact::setFrictionDirection1(const ODEVector3 &v)
{
	ODEVector3 v2(v);

	this->contact.fdir1[0] = (dReal)v2[0];
	this->contact.fdir1[1] = (dReal)v2[1];
	this->contact.fdir1[2] = (dReal)v2[2];
	this->contact.surface.mode |= (int)FrictionDirection1;
}



/// Coeficiente da fricção de colombo. Deve ser um valor entre 0 e ODEInfinity.
/// 0 represena um contacto sem fricção, enquanto ODEInfinity representa um contacto
/// que nunca escorrega.
void ODEContact::setCoulombFriction(ODEReal mu, ODEReal mu2)
{
	this->contact.surface.mu = mu;

	if (mu2 >= 0)
	{
		this->contact.surface.mu2 = mu2;
		this->contact.surface.mode |= (int)AdditionalFriction;
	}
}



/// Define o "ressalto" do contacto. Deve ser um valor entre 0 e 1. 0 significa
/// sem bounce e 1 é o máximo de ressalto.
void ODEContact::setBouncyness(ODEReal bouncyness, ODEReal velocityThreshold)
{
	this->contact.surface.bounce = bouncyness;

	if (velocityThreshold >= 0)
	{
		this->contact.surface.bounce_vel = velocityThreshold;
	}
	this->contact.surface.mode |= (int)Bounce;
}



/// Define o ERP (Error Reduction Parameter) e o CFM (Constraint Force Mixing)
/// da normal do contact. Servem para fazer a superfície "soft".
void ODEContact::setSoftness(ODEReal erp, ODEReal cfm)
{
	this->contact.surface.soft_erp = erp;
	this->contact.surface.soft_cfm = cfm;
	this->contact.surface.mode |= (int)SoftERP;
	this->contact.surface.mode |= (int)SoftCFM;
}



/// Se for usado, assume-se que a superfície de contacto está a mover-se
/// independentemente do movimento dos corpos. Quando usado define a velocidade
/// da superfície de contacto na direcção de fricção 1.
void ODEContact::setIndependentMotion(ODEReal velocity, ODEReal velocity2)
{
	this->contact.surface.motion1 = velocity;
	this->contact.surface.mode |= (int)Motion1;

	if (velocity2 >= 0)
	{
		this->contact.surface.motion2 = velocity2;
		this->contact.surface.mode |= (int)Motion2;
	}
}



/// FDS é um efeito que faz com que as superfícies de contacto fiquem lado a lado
/// com uma velocidade proporcional à força que está a ser aplicada tangencialmente
/// à superfície.
void ODEContact::setForceDependentSlip(ODEReal fds, ODEReal fds2)
{
	this->contact.surface.slip1 = fds;
	this->contact.surface.mode |= (int)Slip1;

	if (fds2 >= 0)
	{
		setForceDependentSlip2(fds2);
	}
}



/// Define FDS na direcção de fricção 2.
void ODEContact::setForceDependentSlip2(ODEReal fds2)
{
	this->contact.surface.slip2 = fds2;
	this->contact.surface.mode |= (int)Slip2;
}



/// Define o modo usado (FrictionPyramids).
void ODEContact::setFrictionMode(Flag flag)
{
	assert(flag == FrictionPyramid1
		|| flag == FrictionPyramid2
		|| flag == BothFrictionPyramids);
	this->contact.surface.mode |= (int)flag;
}



/// Define o contacto.
void ODEContact::setContact(dContact contact)
{
	this->contact = contact;
}



/// Define os parâmetros do contacto a partir de 2 definições de contactos.
/// Usa os valores mais agressivos das 2 definições usado o máximo/mínimo 
/// da mesma variável das 2 definições quando adequado.
void ODEContact::setParameters(const ODEContactDefinition &def1
			, const ODEContactDefinition &def2)
{
	/// Bounce
	if (def1.useBouncyness() || def2.useBouncyness())
	{
		ODEReal bounce = max(def1.getBouncyness(), def2.getBouncyness());

		if (def1.useVelocityThreshold() || def2.useVelocityThreshold())
		{
			this->setBouncyness(bounce
				, getMin(def1.getVelocityThreshold(), def2.getVelocityThreshold()));
		}
		else
		{
			this->setBouncyness(bounce);
		}
	}

	/// ERP, CFM
	if ( (def1.useERP() || def2.useERP()) && (def1.useCFM() || def2.useCFM()) )
	{
		ODEReal cfm, erp = max(def1.getERP(), def2.getERP());

		if (def1.useCFM() && def2.useCFM())
		{
			cfm = def1.getCFM() + def2.getCFM();
		}
		else
		{
			cfm = (def1.useCFM() ? def1.getCFM() : def2.getCFM());
		}
		this->setSoftness(erp, cfm);
	}

	/// Mu
	if (def1.useMu() || def2.useMu())
	{
		ODEReal mu = getMin(def1.getMu(), def2.getMu());

		if (def2.useMu2() || def2.useMu2())
		{
			this->setCoulombFriction(mu
				, getMin(def1.getMu2(), def2.getMu2()));
		}
		else
		{
			this->setCoulombFriction(mu);
		}
	}

	/// Velocity
	if (def1.useVelocity() || def2.useVelocity())
	{
		ODEReal vel = max(def1.getVelocity(), def2.getVelocity());

		if (def1.useVelocity2() || def2.useVelocity2())
		{
			this->setIndependentMotion(vel
				, max(def1.getVelocity2(), def2.getVelocity2()));
		}
		else
		{
			this->setIndependentMotion(vel);
		}
	}

	/// FDS
	if (def1.useFDS() || def2.useFDS())
	{
		ODEReal fds = max(def1.getFDS(), def2.getFDS());

		if (def1.useFDS2() || def2.useFDS2())
		{
			this->setForceDependentSlip(fds
				, max(def1.getFDS2(), def2.getFDS2()));
		}
		else
		{
			this->setForceDependentSlip(fds);
		}
	}
}



/// Devolve o menor dos dois números (se ambos forem positivos).
/// Se só houver um número positivo, devolve esse.
ODEReal ODEContact::getMin(ODEReal r, ODEReal r2)
{
	if ( (r >= 0) && (r2 >= 0) )
	{
		return min(r, r2);
	}

	return (r >= 0 ? r : r2);
}



/// Devolve a posição do ponto de contacto.
const ODEVector3 ODEContact::getPosition() const
{
	return ODEVector3((ODEReal)this->contact.geom.pos[0]
				, (ODEReal)this->contact.geom.pos[1]
				, (ODEReal)this->contact.geom.pos[2]);
}



/// Devolve a normal do contacto.
const ODEVector3 ODEContact::getNormal() const
{
	return ODEVector3((ODEReal)this->contact.geom.normal[0]
				, (ODEReal)this->contact.geom.normal[1]
				, (ODEReal)this->contact.geom.normal[2]);
}



/// Devolve a penetração do contacto.
ODEReal ODEContact::getDepth() const
{
	return (ODEReal)this->contact.geom.depth;
}



/// Devolve o contacto.
dContact ODEContact::getContact() const
{
	return this->contact;
}