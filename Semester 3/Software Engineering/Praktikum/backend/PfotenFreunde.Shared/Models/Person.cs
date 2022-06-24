using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Person : User
{
    public Person()
    {
        Pets = new HashSet<Pet>();
    }

    public string Surname { get; set; } = null!;
    public int Age { get; set; }
    public string Sex { get; set; } = null!;
    public int? InstitutionId { get; set; }

    [JsonIgnore]
    public virtual Institution? Institution { get; set; }
    [JsonIgnore]
    public virtual ICollection<Pet> Pets { get; set; }
}
