import os

from mastodon import Mastodon


def mastodon_login(login, passe):
    "Connexion à l'instance mastodon, retourne un objet api mastodon"
    instance = login.split('@')[1]

    # Mastodon.create_app(
    #     'pytooterapp',
    #     api_base_url='https://mastodon.social',
    #     to_file='pytooter_clientcred.secret'
    # )

    mastodon = Mastodon(client_id='pytooter_clientcred.secret', )
    mastodon.log_in(
        login,
        passe,
        to_file='pytooter_usercred.secret'
    )

    return mastodon

if __name__ == '__main__':
    m = mastodon_login("contact@cyrilvincent.com", "MT%2b?$5#6FW-%j")