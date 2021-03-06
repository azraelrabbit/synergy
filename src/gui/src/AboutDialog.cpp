/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2008 Volker Lanz (vl@fidra.de)
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AboutDialog.h"

#include <QtCore>
#include <QtGui>
#include <QClipboard>

const static char version[] = _SYN_VERSION "_" _GIT_BRANCH "_" _GIT_REVISION;

void AboutDialog::on_m_pButtonCopy_clicked() {
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(QString(version));
}

AboutDialog::AboutDialog(QWidget* parent, const QString& synergyApp) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
	Ui::AboutDialogBase()
{
	setupUi(this);

	m_versionChecker.setApp(synergyApp);
	m_pLabelSynergyVersion->setText(QString(version));

#ifdef _USE_C_DATE
	QString buildDateString = QString::fromLocal8Bit(__DATE__).simplified();
#else
	QString buildDateString = QString("Jan 1 2000");
#endif
	QDate buildDate = QLocale("en_US").toDate(buildDateString, "MMM d yyyy");
	m_pLabelBuildDate->setText(buildDate.toString(Qt::SystemLocaleLongDate));

	// change default size based on os
#if defined(Q_OS_MACOS)
	QSize size(600, 380);
	setMaximumSize(size);
	setMinimumSize(size);
	resize(size);
#elif defined(Q_OS_LINUX)
	QSize size(600, 330);
	setMaximumSize(size);
	setMinimumSize(size);
	resize(size);
#endif
}
