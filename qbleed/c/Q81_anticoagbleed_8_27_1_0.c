/* 
 * Copyright 2014 ClinRisk Ltd.
 * 
 * This file is part of QBleed (http://qbleed.org, http://svn.clinrisk.co.uk/opensource/qbleed).
 * 
 * QBleed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * QBleed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with QBleed.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Additional terms
 * 
 * The following disclaimer must be displayed alongside any risk score generated by this code.
 *   The initial version of this file, to be found at http://svn.clinrisk.co.uk/opensource/qbleed, faithfully implements QBleed.
 *   We have released this code under the GNU Affero General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Affero General Public License is such that we cannot prevent, for example, someone accidentally 
 *   altering the coefficients, getting the inputs wrong, or just poor programming.
 *   We stress, therefore, that it is the responsibility of the end user to check that the source that they receive produces the same results as the original code posted at http://svn.clinrisk.co.uk/opensource/qbleed.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 * 
 * This file has been auto-generated.
 * XML source: Q81_anticoagbleed_8_27_1_0.xml
 * STATA dta time stamp: 25 Jan 2014 20:52
 * This file was created on: Tue 29 Jul 2014 14:05:50 BST
 */

#include <math.h>
#include <string.h>
#include <clinrisk/Q81_anticoagbleed_8_27_1_0.h>
#include <clinrisk/utils.h>

static double Q81_anticoagbleed_8_27_1_female_raw(
int age,int alcohol_cat6,int b_AF,int b_anticonvulsant,int b_antidepressant,int b_antiplat,int b_anycancer,int b_ccf,int b_corticosteroids,int b_liverpancreas,int b_nsaid,int b_platlet,int b_treatedhyp,int b_varices,int b_vte,double bmi,int ethrisk,int exp_anticoagulant,int prior_anybleed,int smoke_cat,int surv,double town
)
{
	double survivor[6] = {
		0,
		0.999559581279755,
		0,
		0,
		0,
		0.996977329254150
	};

	/* The conditional arrays */

	double Ialcohol[6] = {
		0,
		-0.1354293067354592500000000,
		-0.2304092681009215500000000,
		-0.0068094997644066032000000,
		0.6143597005611164400000000,
		1.0478226630063583000000000
	};
	double Iethrisk[10] = {
		0,
		0,
		-0.0408714479974104510000000,
		-0.0150663434302572010000000,
		-0.1284858322808346300000000,
		-0.2114331714063828200000000,
		0.1298215752670493800000000,
		-0.6113056492207671300000000,
		0.0505482677860789600000000,
		0.0380209685943937930000000
	};
	double Ismoke[5] = {
		0,
		0.0862933285920386290000000,
		0.2721508426463970000000000,
		0.2650964225184774800000000,
		0.4440218913177809100000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dage = age;
	dage=dage/10;
	double age_1 = pow(dage,-1);
	double age_2 = pow(dage,3);
	double dbmi = bmi;
	dbmi=dbmi/10;
	double bmi_1 = pow(dbmi,-2);
	double bmi_2 = pow(dbmi,-2)*log(dbmi);

	/* Centring the continuous variables */

	age_1 = age_1 - 0.216344222426414;
	age_2 = age_2 - 98.756134033203125;
	bmi_1 = bmi_1 - 0.151425197720528;
	bmi_2 = bmi_2 - 0.142919912934303;
	town = town - 0.234209924936295;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Ialcohol[alcohol_cat6];
	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age_1 * -0.2299094645561103600000000;
	a += age_2 * 0.0030559902343811176000000;
	a += bmi_1 * 1.6886521089009670000000000;
	a += bmi_2 * -3.6798580730004282000000000;
	a += town * 0.0214223159932329650000000;

	/* Sum from boolean values */

	a += b_AF * 0.2163711499482285100000000;
	a += b_anticonvulsant * 0.3351170785774408900000000;
	a += b_antidepressant * 0.4538754610284977400000000;
	a += b_antiplat * 0.2281833926626009600000000;
	a += b_anycancer * 0.1965191842576379500000000;
	a += b_ccf * 0.3428279076381805500000000;
	a += b_corticosteroids * 0.2288083293387852500000000;
	a += b_liverpancreas * 1.0321197951183290000000000;
	a += b_nsaid * 0.1505067363810720400000000;
	a += b_platlet * 0.5175774687855455600000000;
	a += b_treatedhyp * 0.0617117043937011540000000;
	a += b_varices * 1.2077662000034650000000000;
	a += b_vte * 0.1514985711271303000000000;
	a += exp_anticoagulant * 1.3580150446439490000000000;
	a += prior_anybleed * 0.8163544836661362800000000;

	/* Sum from interaction terms */

	a += age_1 * exp_anticoagulant * 3.3525627663237709000000000;
	a += age_1 * prior_anybleed * 2.2212270202734836000000000;
	a += age_2 * exp_anticoagulant * -0.0004193413226610703300000;
	a += age_2 * prior_anybleed * -0.0006436703717367378000000;

	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}

static int Q81_anticoagbleed_8_27_1_female_validation(
int age,int alcohol_cat6,int b_AF,int b_anticonvulsant,int b_antidepressant,int b_antiplat,int b_anycancer,int b_ccf,int b_corticosteroids,int b_liverpancreas,int b_nsaid,int b_platlet,int b_treatedhyp,int b_varices,int b_vte,double bmi,int ethrisk,int exp_anticoagulant,int prior_anybleed,int smoke_cat,int surv,double town,char *errorBuf,int errorBufSize
)
{
	int ok=1;
	*errorBuf=0;
	if (!i_in_range(age,21,99)) {
		ok=0;
		strlcat(errorBuf,"error: age must be in range (21,99)\n",errorBufSize);
	}
	if (!i_in_range(alcohol_cat6,0,5)) {
		ok=0;
		strlcat(errorBuf,"error: alcohol_cat6 must be in range (0,5)\n",errorBufSize);
	}
	if (!is_boolean(b_AF)) {
		ok=0;
		strlcat(errorBuf,"error: b_AF must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_anticonvulsant)) {
		ok=0;
		strlcat(errorBuf,"error: b_anticonvulsant must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_antidepressant)) {
		ok=0;
		strlcat(errorBuf,"error: b_antidepressant must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_antiplat)) {
		ok=0;
		strlcat(errorBuf,"error: b_antiplat must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_anycancer)) {
		ok=0;
		strlcat(errorBuf,"error: b_anycancer must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_ccf)) {
		ok=0;
		strlcat(errorBuf,"error: b_ccf must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_corticosteroids)) {
		ok=0;
		strlcat(errorBuf,"error: b_corticosteroids must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_liverpancreas)) {
		ok=0;
		strlcat(errorBuf,"error: b_liverpancreas must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_nsaid)) {
		ok=0;
		strlcat(errorBuf,"error: b_nsaid must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_platlet)) {
		ok=0;
		strlcat(errorBuf,"error: b_platlet must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_treatedhyp)) {
		ok=0;
		strlcat(errorBuf,"error: b_treatedhyp must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_varices)) {
		ok=0;
		strlcat(errorBuf,"error: b_varices must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_vte)) {
		ok=0;
		strlcat(errorBuf,"error: b_vte must be in range (0,1)\n",errorBufSize);
	}
	if (!d_in_range(bmi,20,40)) {
		ok=0;
		strlcat(errorBuf,"error: bmi must be in range (20,40)\n",errorBufSize);
	}
	if (!i_in_range(ethrisk,1,9)) {
		ok=0;
		strlcat(errorBuf,"error: ethrisk must be in range (1,9)\n",errorBufSize);
	}
	if (!is_boolean(exp_anticoagulant)) {
		ok=0;
		strlcat(errorBuf,"error: exp_anticoagulant must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(prior_anybleed)) {
		ok=0;
		strlcat(errorBuf,"error: prior_anybleed must be in range (0,1)\n",errorBufSize);
	}
	if (!i_in_range(smoke_cat,0,4)) {
		ok=0;
		strlcat(errorBuf,"error: smoke_cat must be in range (0,4)\n",errorBufSize);
	}
	if ( !(surv==1 || surv==5) ) {
		ok=0;
		strlcat(errorBuf,"error: surv must be 1 or 5\n",errorBufSize);
	}
	if (!d_in_range(town,-7,11)) {
		ok=0;
		strlcat(errorBuf,"error: town must be in range (-7,11)\n",errorBufSize);
	}
	return ok;
}

double Q81_anticoagbleed_8_27_1_female(
int age,int alcohol_cat6,int b_AF,int b_anticonvulsant,int b_antidepressant,int b_antiplat,int b_anycancer,int b_ccf,int b_corticosteroids,int b_liverpancreas,int b_nsaid,int b_platlet,int b_treatedhyp,int b_varices,int b_vte,double bmi,int ethrisk,int exp_anticoagulant,int prior_anybleed,int smoke_cat,int surv,double town,int *error,char *errorBuf,int errorBufSize
)
{
	*error = 0;	int ok = Q81_anticoagbleed_8_27_1_female_validation(age,alcohol_cat6,b_AF,b_anticonvulsant,b_antidepressant,b_antiplat,b_anycancer,b_ccf,b_corticosteroids,b_liverpancreas,b_nsaid,b_platlet,b_treatedhyp,b_varices,b_vte,bmi,ethrisk,exp_anticoagulant,prior_anybleed,smoke_cat,surv,town,errorBuf,errorBufSize);
	if(!ok) { 
		*error = 1;
		return 0.0;
	}
	return Q81_anticoagbleed_8_27_1_female_raw(age,alcohol_cat6,b_AF,b_anticonvulsant,b_antidepressant,b_antiplat,b_anycancer,b_ccf,b_corticosteroids,b_liverpancreas,b_nsaid,b_platlet,b_treatedhyp,b_varices,b_vte,bmi,ethrisk,exp_anticoagulant,prior_anybleed,smoke_cat,surv,town);
}
