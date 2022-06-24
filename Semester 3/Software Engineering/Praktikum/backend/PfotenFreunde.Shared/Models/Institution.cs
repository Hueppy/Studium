using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Institution : User
{
	public Institution()
	{
		People = new HashSet<Person>();
	}

    public string? Homepage { get; set; }

    [JsonIgnore]
    public virtual ICollection<Person> People { get; set; }
}
