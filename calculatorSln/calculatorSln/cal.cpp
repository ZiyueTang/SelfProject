#include "cal.h"

calculator::calculator(QWidget *parent) :QDialog(parent) {
	l_exp = new QLabel(this);
	l_input = new QLabel(this);
	l_exp->setAlignment(Qt::AlignRight);
	l_input->setAlignment(Qt::AlignRight);
	l_exp->setText(tr(""));
	l_input->setText(tr("0"));

	QFont font;
	font.setPixelSize(50);
	l_input->setFont(font);

	QString array[24] = { "(","sqrt","sqare","1/x",")","c","<-","%",
		"7","8","9","*","4","5","6","-","1","2","3","+","+-","0",".","=" };
	
	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->addWidget(l_exp, 0, 0, 1, 4);
	mainLayout->addWidget(l_input, 1, 0, 1, 4);
	int time = 0;
	int index = 0;
	for (int row = 0; row < 6; row++) {
		for (int col = 0; col < 4; col++) {
			index = time + col;
			btn[index] = new QPushButton(this);
			btn[index]->setText(array[index]);//给每个按钮设置文本
			mainLayout->addWidget(btn[index], row + 2, col);//给每个按钮设置布局
			connect(btn[index], SIGNAL(clicked()), this, SLOT(click()));//给每个按钮设置连接
		}
		time += 4;
	}
}

calculator::~calculator(){}

void calculator::click() {
	QPushButton *obj = (QPushButton*)sender();
	QString text = obj->text();

	if (isNum(text)) {
		if (!expression.isEmpty() && (isNum(expression.last()) || expression.last() == ".")) {
			text = l_input->text() + text;
			l_input->setText(text);
		}
		else {//新的数字
			l_input->setText(text);
		}
	}
	else if(text == "."){
		l_input->setText(l_input->text() + text);
	}
	else if (text == "<-") {
		QString s = l_input->text();
		l_input->setText(s.remove(s.length()-1, 1));
		if(l_input->text().isEmpty())
			l_input->setText(tr("0"));
	}
	else if (text == "c") {
		expression.clear();
		operands.clear();
		operators.clear();
		l_input->setText(tr("0"));
		l_exp->setText(tr(""));
	}
	else if (text == "1/x") {
		QString val = l_input->text();
		if (val.contains("/")) {
			l_input->setText(val.remove(0, 2));
		}
		else
			l_input->setText(val.insert(0, "1/"));
	}
	else if (text == "+-") {
		if (l_input->text().at(0) == "-")
			l_input->setText(l_input->text().remove(0, 1));
		else
			l_input->setText(l_input->text().insert(0, "-"));
	}
	else if (text == "sqrt") {
		double val = calOperand();
		l_exp->setText(l_exp->text() + "sqrt(" + l_input->text() + ")");
		l_input->setText(QString::number(qSqrt(val), 'g', 6));
	}
	else if (text == "sqare") {
		double val = calOperand();
		if (expression.last() == ")" || expression.last() == "sqrt" || expression.last() == "sqare")
			l_exp->setText(l_exp->text() + "^2");
		else
			l_exp->setText(l_exp->text() + l_input->text() + "^2");
		l_input->setText(QString::number(pow(val, 2), 'g', 6));
	}
	else if (text == "(") {
		l_exp->setText(l_exp->text() + text);
		operators.push(text);
	}
	else {
		operands.push(calOperand());//把上一个操作数或计算结果进栈

		if (text == "+" || text == "-") {
			if (operators.contains("("))
				cal_in();
			else
				while (!operators.isEmpty())
					cal_all();
			
			if (expression.last() == ")" || expression.last() == "sqrt" || expression.last() == "sqare")
				l_exp->setText(l_exp->text() + text);
			else
				l_exp->setText(l_exp->text() + l_input->text() + text);

			l_input->setText(QString::number(operands.top(), 'g', 6));
			operators.push(text);
		}
		else if (text == "*" || text == "%") {
			while (!operators.isEmpty() && (operators.top() == "*" || operators.top() == "%")) {
				cal_mul();
			}
		
			if(expression.last() == ")" || expression.last() == "sqrt" || expression.last() == "sqare")
				l_exp->setText(l_exp->text() + text);
			else
				l_exp->setText(l_exp->text() + l_input->text() + text);

			l_input->setText(QString::number(operands.top(), 'g', 6));
			operators.push(text);
		}
		else if (text == ")") {
			cal_in();
			l_exp->setText(l_exp->text() + l_input->text() + text);
			l_input->setText(QString::number(operands.pop(), 'g', 6));
			operators.pop();
		}
		else if (text == "=") {
			expression.clear();
			l_exp->setText(tr(""));
			l_input->setText(QString::number(cal_res(), 'g', 6));
		}
		
	}

	expression.push_back(text);
}

bool calculator::isNum(QString s) {
	if (s != "1/x" && s >= "0" && s <= "9")
		return true;
	else
		return false;
}

void calculator::cal_all() {
	QString op = operators.pop();
	if (op == "+") {
		double v1 = operands.pop();
		double v2 = operands.pop();
		operands.push(v1 + v2);
	}
	else if (op == "-") {
		double v1 = operands.pop();
		double v2 = operands.pop();
		operands.push(v2 - v1);
	}
	else if (op == "*") {
		double v1 = operands.pop();
		double v2 = operands.pop();
		operands.push(v1 * v2);
	}
	else if (op == "%") {
		double v1 = operands.pop();
		double v2 = operands.pop();
		operands.push(v2 / v1);
	}
}

void calculator::cal_in() {
	while (operators.top() != "(")
		cal_all();
}

void calculator::cal_mul() {
	double v1 = operands.pop();
	double v2 = operands.pop();
	QString op = operators.pop();
	if (op == "*")
		operands.push(v1 * v2);
	else if (op == "%")
		operands.push(v2 / v1);
}

double calculator::cal_res() {
	while (!operators.isEmpty()) {
		cal_all();
	}
		
	return operands.top();
}

double calculator::calOperand() {
	bool ok;
	double operand;
	QString input = l_input->text();
	if (input.contains("/")) {
		QString s1 = input.split("/")[0];
		QString s2 = input.split("/")[1];
		operand = s1.toDouble(&ok) / s2.toDouble(&ok);
	}
	else
		operand = input.toDouble(&ok);
	return operand;
}