#include "coonscalculator.hpp"



CoonsCalculator::CoonsCalculator()
{
}


CoonsCalculator::~CoonsCalculator()
{
}

void CoonsCalculator::getCoonsPatch(QVector4DMatrix& ltrb, QVector4DMatrix* patch, float precision_u, float precision_v) {
	if (!patch || ltrb.isEmpty() || ltrb.size() < 4) {
		patch = nullptr;
		return;
	}
	int size = ltrb[0].size();
	for (int i = 1; i < ltrb.size(); i++) {
		if (ltrb[i].size() != size) {
			patch = nullptr;
			return;
		}
	}
	QVector4DMatrix rc;
	QVector4DMatrix rd;
	QVector4DMatrix rcd;
	for (int k = 0; k < ltrb[0].size(); k++) {
		QVector<QVector4D> row_rc;
		for (int vAsInt = 0; vAsInt <= 100; vAsInt += (precision_u * 100)) {
			double v = vAsInt / 100.f;
			QVector4D curr_rc = ltrb[0][k] * (1 - v) + ltrb[2][k] * v;
			row_rc.push_back(curr_rc);

		}
		rc.push_back(row_rc);
	}
	for (int k = 0; k < ltrb[0].size(); k++) {
		QVector<QVector4D> row_rd;
		for (int uAsInt = 0; uAsInt <= 100; uAsInt += (precision_u * 100)) {
			double u = uAsInt / 100.f;
			QVector4D curr_rd = ltrb[3][k] * (1 - u) + ltrb[1][k] * u;
			row_rd.push_back(curr_rd);

		}
		rd.push_back(row_rd);
	}
	for (int uAsInt = 0; uAsInt <= 100; uAsInt += (precision_u * 100)) {
		double u = uAsInt / 100.f;
		QVector<QVector4D> row_rc;
		for (int vAsInt = 0; vAsInt <= 100; vAsInt += (precision_v * 100)) {
			double v = vAsInt / 100.f;
			QVector4D curr_rc = ltrb[0][0] * (1 - u) * (1 - v) + ltrb[1][0] * v * (1 - u) + ltrb[3].last() * (1 - v)*u + ltrb[2].last()  * u * v;
			row_rc.push_back(curr_rc);
		}
		rcd.push_back(row_rc);
	}
	for (int m = 0; m < rc.size(); m++) {
		QVector<QVector4D> interpolated_row;
		for (int n = 0; n < rc[0].size(); n++) {
			interpolated_row.push_back((rc[m][n] + rd[m][n]) - rcd[m][n]);
			//	interpolated_row.push_back(rcd[m][n]);
				//interpolated_row.push_back(rd[m][n]);
				//interpolated_row.push_back(rc[m][n]);
		}
		patch->push_back(interpolated_row);
	}
}

