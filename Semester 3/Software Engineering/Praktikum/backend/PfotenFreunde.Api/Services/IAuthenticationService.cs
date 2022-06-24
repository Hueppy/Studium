using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Services;

public interface IAuthenticator
{
	Task<Login> Authenticate(string email, string password);	
}
