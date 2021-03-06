/* 
 * Copyright 2014-5 ClinRisk Ltd.
 * 
 * This file is part of QRISK2-2015 (http://qrisk.org, http://qrisk.org/QRISK2-2015-lgpl-source.tgz).
 * 
 * QRISK2-2015 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * QRISK2-2015 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with QRISK2-2015.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional terms
 *
 * The following disclaimer must be held together with any risk score score generated by this code.  
 * If the score is displayed, then this disclaimer must be displayed or otherwise be made easily accessible, e.g. by a prominent link alongside it.
 *   The initial version of this file, to be found at http://qrisk.org/QRISK2-2015-lgpl-source.tgz, faithfully implements QRISK2-2015.
 *   ClinRisk Ltd. have released this code under the GNU Lesser General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Lesser General Public License is such that we cannot prevent, for example, someone accidentally
 *   altering the coefficients, getting the inputs wrong, or just poor programming.
 *   ClinRisk Ltd. stress, therefore, that it is the responsibility of the end user to check that the source that 
 *   they receive produces the same results as the original code posted at http://qrisk.org/QRISK2-2015-lgpl-source.tgz.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 * 
 * End of additional terms
 */

#include <math.h>
#include <string.h>

static double cvd_male_raw(
int age,int b_AF,int b_ra,int b_renal,int b_treatedhyp,int b_type1,int b_type2,double bmi,int ethrisk,int fh_cvd,double rati,double sbp,int smoke_cat,int surv,double town
)
{
	double survivor[16] = {
		0,
		0.998205721378326,
		0.996380507946014,
		0.994511783123016,
		0.992520809173584,
		0.990338504314423,
		0.988223373889923,
		0.986053407192230,
		0.983751118183136,
		0.981297850608826,
		0.978794217109680,
		0.976175725460052,
		0.973336458206177,
		0.970354199409485,
		0.967230498790741,
		0.963918387889862
	};

	/* The conditional arrays */

	double Iethrisk[10] = {
		0,
		0,
		0.3173321430481919100000000,
		0.4738590786081115500000000,
		0.5171314655968145500000000,
		0.1370301157366419200000000,
		-0.3885522304972663900000000,
		-0.3812495485312194500000000,
		-0.4064461381650994500000000,
		-0.2285715521377336100000000
	};
	double Ismoke[5] = {
		0,
		0.2684479158158020200000000,
		0.6307674973877591700000000,
		0.7178078883378695700000000,
		0.8704172533465485100000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dage = age;
	dage=dage/10;
	double age_1 = pow(dage,-1);
	double age_2 = pow(dage,2);
	double dbmi = bmi;
	dbmi=dbmi/10;
	double bmi_2 = pow(dbmi,-2)*log(dbmi);
	double bmi_1 = pow(dbmi,-2);

	/* Centring the continuous variables */

	age_1 = age_1 - 0.233734160661697;
	age_2 = age_2 - 18.304403305053711;
	bmi_1 = bmi_1 - 0.146269768476486;
	bmi_2 = bmi_2 - 0.140587374567986;
	rati = rati - 4.321151256561279;
	sbp = sbp - 130.589752197265620;
	town = town - 0.551009356975555;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age_1 * -18.0437312550377270000000000;
	a += age_2 * 0.0236486454254306940000000;
	a += bmi_1 * 2.5388084343581578000000000;
	a += bmi_2 * -9.1034725871528597000000000;
	a += rati * 0.1684397636136909500000000;
	a += sbp * 0.0105003089380754820000000;
	a += town * 0.0323801637634487590000000;

	/* Sum from boolean values */

	a += b_AF * 1.0363048000259454000000000;
	a += b_ra * 0.2519953134791012600000000;
	a += b_renal * 0.8359352886995286000000000;
	a += b_treatedhyp * 0.6603459695917862600000000;
	a += b_type1 * 1.3309170433446138000000000;
	a += b_type2 * 0.9454348892774417900000000;
	a += fh_cvd * 0.5986037897136281500000000;

	/* Sum from interaction terms */

	a += age_1 * (smoke_cat==1) * 0.6186864699379683900000000;
	a += age_1 * (smoke_cat==2) * 1.5522017055600055000000000;
	a += age_1 * (smoke_cat==3) * 2.4407210657517648000000000;
	a += age_1 * (smoke_cat==4) * 3.5140494491884624000000000;
	a += age_1 * b_AF * 8.0382925558108482000000000;
	a += age_1 * b_renal * -1.6389521229064483000000000;
	a += age_1 * b_treatedhyp * 8.4621771382346651000000000;
	a += age_1 * b_type1 * 5.4977016563835504000000000;
	a += age_1 * b_type2 * 3.3974747488766690000000000;
	a += age_1 * bmi_1 * 33.8489881012767600000000000;
	a += age_1 * bmi_2 * -140.6707025404897100000000000;
	a += age_1 * fh_cvd * 2.0858333154353321000000000;
	a += age_1 * sbp * 0.0501283668830720540000000;
	a += age_1 * town * -0.1988268217186850700000000;
	a += age_2 * (smoke_cat==1) * -0.0040893975066796338000000;
	a += age_2 * (smoke_cat==2) * -0.0056065852346001768000000;
	a += age_2 * (smoke_cat==3) * -0.0018261006189440492000000;
	a += age_2 * (smoke_cat==4) * -0.0014997157296173290000000;
	a += age_2 * b_AF * 0.0052471594895864343000000;
	a += age_2 * b_renal * -0.0179663586193546390000000;
	a += age_2 * b_treatedhyp * 0.0092088445323379176000000;
	a += age_2 * b_type1 * 0.0047493510223424558000000;
	a += age_2 * b_type2 * -0.0048113775783491563000000;
	a += age_2 * bmi_1 * 0.0627410757513945650000000;
	a += age_2 * bmi_2 * -0.2382914909385732100000000;
	a += age_2 * fh_cvd * -0.0049971149213281010000000;
	a += age_2 * sbp * -0.0000523700987951435090000;
	a += age_2 * town * -0.0012518116569283104000000;

	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}
