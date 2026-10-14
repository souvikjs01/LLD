package example

import "fmt"

type DBConnection interface {
	Connect() error
}

type MongoDB struct {
	MongoUri string
}

func (m *MongoDB) Connect() error {
	fmt.Println("Mongodb is connected", m.MongoUri)
	return nil
}

type PostgresDB struct {
	PgUri string
}

func (p *PostgresDB) Connect() error {
	fmt.Println("Postgres db is connected", p.PgUri)
	return nil
}

type Redis struct {
	RedisUri string
}

func (r *Redis) Connect() error {
	fmt.Println("Redis is connected", r.RedisUri)
	return nil
}

type DBService struct {
	DBConnection
}

func (d *DBService) SetDatabase(db DBConnection) {
	d.DBConnection = db
}

func (d *DBService) Connect() error {
	if d.DBConnection == nil {
		return fmt.Errorf("database is not defined")
	}
	return d.DBConnection.Connect()
}
