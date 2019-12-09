#ifndef CAL_H
#define CAL_H

#include <QtWidgets>

class calculator :public QDialog {
	Q_OBJECT
public:
	calculator(QWidget *parent = 0);
	~calculator();
	bool isNum(QString s);//判断所点击的字符串是否是数字，是返回true，否则返回false
	void cal_all();//遇到加减号时计算的函数
	void cal_in();//计算括号里的值
	void cal_mul();//计算栈中所有的乘法运算
	double cal_res();//点击等于号时计算最终的值
	double calOperand();//将输入框中输入的数字或显示的结果，字符串转成double型，并将操作数入栈

private:
	QLabel *l_exp;//表达式label
	QLabel *l_input;//输入框label
	QPushButton *btn[24];//24个按钮，用数组声明

	QStack<double> operands;//操作数栈
	QStack<QString> operators;//操作符栈
	QVector<QString> expression;//表达式数组，用来记录当前表达式

private slots:
	void click();//槽函数，用来响应24个按钮
};

#endif 
