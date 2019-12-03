#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys

from builtins import ImportError
from django.http import HttpResponse
from django.template import Context,loader

def main():
    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hello_django.settings')
    try:
        from django.core.management import execute_from_command_line
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        )(exc)
    execute_from_command_line(sys.argv)

def index(request):
    template = loader.get_template("Modelo\ Unit/index.html")
    template.render()
    return HttpResponse(template.render)


if __name__ == '__main__':
    main()
