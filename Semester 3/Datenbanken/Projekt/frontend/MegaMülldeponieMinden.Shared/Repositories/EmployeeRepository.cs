using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class EmployeeRepository : Repository<Employee>
{
    private readonly Repository<Address> addressRepository;
    private readonly Repository<EmployeeKind> kindRepository;
    
    public EmployeeRepository(
        IConnector connector,
        Repository<Address> addressRepository,
        Repository<EmployeeKind> kindRepository) : base(connector)
    {
        this.addressRepository = addressRepository;
        this.kindRepository = kindRepository;
    }

    protected override string Table => "PERSONAL";
    protected override string KeyField => "ID_PERSONAL";

    protected override string Insert => @"
INSERT INTO PERSONAL
  (NAME_PERSONAL, VORNAME_PERSONAL, GEBURTSTAG_PERSONAL, ID_ADRESSE, CHEF_ID_PERSONAL, ID_PERSONALART, FUEHRERSCHEIN_PERSONAL, GEHALT_PERSONAL_MONAT, ID_PERSONAL)
VALUES
  (:Name, :FirstName, SYSDATE, :Address, :Superior, :Kind, :License, :Salary, :Id)";

    protected override string Update => @"
UPDATE PERSONAL 
SET 
  NAME_PERSONAL = :Name, 
  VORNAME_PERSONAL = :FirstName, 
  ID_ADRESSE = :Address, 
  CHEF_ID_PERSONAL = :Superior, 
  ID_PERSONALART = :Kind,
  FUEHRERSCHEIN_PERSONAL = :License,
  GEHALT_PERSONAL_MONAT = :Salary
WHERE 
  ID_PERSONAL = :Id";

    protected override async Task Read(Employee obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_PERSONAL") ?? string.Empty;
        obj.FirstName = await row.AsString("VORNAME_PERSONAL") ?? string.Empty;
        obj.Birthdate = await row.AsDateTime("GEBURTSTAG_PERSONAL") ?? DateTime.Now;
        obj.Address = await this.addressRepository.Load(await row.AsInt("ID_ADRESSE") ?? -1);
        obj.Superior = await Load(await row.AsInt("CHEF_ID_PERSONAL") ?? -1);
        obj.Kind = await this.kindRepository.Load(await row.AsInt("ID_PERSONALART") ?? -1);
        obj.License = await row.AsString("FUEHRERSCHEIN_PERSONAL") ?? string.Empty;
        obj.Salary = await row.AsInt("GEHALT_PERSONAL_MONAT") ?? -1;
    }

    protected override void Write(Employee obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("FirstName", obj.FirstName);
        parameters.Add("Address", obj.Address.Id);
        parameters.Add("Superior", obj.Superior?.Id);
        parameters.Add("Kind", obj.Kind?.Id);
        parameters.Add("License", string.IsNullOrEmpty(obj.License) ? null : obj.License);
        parameters.Add("Salary", obj.Salary);
        parameters.Add("Id", obj.Id);
    }

    public override async Task Save(Employee obj)
    {
        if (obj.Address != null) {
            await this.addressRepository.Save(obj.Address);
        }
        await base.Save(obj);
    }

    protected override long GetId(Employee obj)
    {
        return obj.Id;
    }


    protected override void SetId(Employee obj, long id)
    {
        obj.Id = id;
    }
}
