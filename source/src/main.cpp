#include <iostream>
#include <QApplication>
#include <QWidget>
#include <SQLiteCpp/SQLiteCpp.h>
#include <qcoreapplication.h>
#include "logindialog.h"

int main(int argc, char** argv){


    
    try
    {
        
        // 1. 打开数据库，不存在则自动创建
        SQLite::Database db("test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
       // std::cout << "SQLite version: " << db.in() << "\n";

        // 2. 创建数据表
        db.exec(R"(
            CREATE TABLE IF NOT EXISTS user(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                age INTEGER,
                score REAL
            )
        )");
        
        // 3. 事务批量插入（原子操作，出错全部回滚）
        SQLite::Transaction tx(db);

        // 方式1：直接执行SQL插入
        db.exec("INSERT INTO user(name, age, score) VALUES('Alice', 22, 95.5)");

        // 方式2：预处理语句，安全防SQL注入（推荐）
        SQLite::Statement stmt(db, "INSERT INTO user(name, age, score) VALUES(?, ?, ?)");
        stmt.bind(1, "Bob");
        stmt.bind(2, 25);
        stmt.bind(3, 88.0);
        stmt.exec();
        stmt.reset(); // 重置语句，复用

        stmt.bind(1, "Charlie");
        stmt.bind(2, 30);
        stmt.bind(3, 76.2);
        stmt.exec();

        tx.commit(); // 提交事务

        // 4. 查询单行单列
        int count = db.execAndGet("SELECT COUNT(*) FROM user");
        std::cout << QString("总用户数：" ).toLocal8Bit().toStdString()<< count << "\n";

        // 5. 遍历多行结果集
        SQLite::Statement query(db, "SELECT id, name, age, score FROM user WHERE age > 22");
        while (query.executeStep())
        {
            int id = query.getColumn(0);
            std::string name = query.getColumn(1).getText();
            int age = query.getColumn(2);
            double score = query.getColumn(3);
            std::cout << id << " | " << name << " | " << age << " | " << score << "\n";
        }

        // 6. 更新数据
        SQLite::Statement update(db, "UPDATE user SET score = ? WHERE name = ?");
        update.bind(1, 99.0);
        update.bind(2, "Bob");
        int affected = update.exec();
        std::cout <<QString("更新影响行数：" ).toLocal8Bit().toStdString()<< affected << "\n";

        // 7. 删除数据
        SQLite::Statement del(db, "DELETE FROM user WHERE name = ?");
        del.bind(1, "Charlie");
        del.exec();

    }
    catch (const SQLite::Exception& e)
    {
        // 捕获数据库异常
        std::cerr << "SQL错误：" << e.what() << "\n";
        return 1;
    }
    
    QApplication a(argc, argv);
   
    LoginDialog l;
    QString s;
    l.show();
    
    a.exec();

    return 0;
}