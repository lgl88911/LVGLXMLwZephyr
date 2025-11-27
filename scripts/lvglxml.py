# Copyright (c) 2025, Frank Li<lgl88911@163.com>

'''lvglxml.py

Import lvgl xml export C code to zephyr app.'''

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output
import subprocess
import os
import shutil

class LvglXmlCommand(WestCommand):

    def __init__(self):
        super().__init__(
            'lvglxml',               # gets stored as self.name
            'Import LVGL XML export C code to Zephyr app',  # self.help
            # self.description:
            '''\
Import LVGL XML export C code to Zephyr app.

This command synchronizes C source files, header files, and build files
from a specified source directory to the app/gui directory of the current
Zephyr project.''')

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        # Add the source path argument
        parser.add_argument('source_path', help='source directory path containing LVGL XML export files')

        return parser           # gets stored as self.parser

    def do_run(self, args, unknown_args):
        # Get the absolute path of the current project
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        target_dir = os.path.join(project_root, 'app', 'gui')
        
        # Check if source path exists
        if not os.path.exists(args.source_path):
            log.err(f"Source path does not exist: {args.source_path}")
            return 1
            
        if not os.path.isdir(args.source_path):
            log.err(f"Source path is not a directory: {args.source_path}")
            return 1
            
        # Handle target directory - delete if exists, then create
        if os.path.exists(target_dir):
            log.inf(f"Target directory exists: {target_dir}")
            log.inf(f"Deleting target directory: {target_dir}")
            try:
                shutil.rmtree(target_dir)
                log.inf(f"Target directory deleted successfully: {target_dir}")
            except Exception as e:
                log.err(f"Failed to delete target directory: {e}")
                return 1
        
        # Create target directory
        log.inf(f"Creating target directory: {target_dir}")
        try:
            os.makedirs(target_dir, exist_ok=True)
            log.inf(f"Target directory created successfully: {target_dir}")
        except Exception as e:
            log.err(f"Failed to create target directory: {e}")
            return 1
            
        # Build the rsync command
        rsync_cmd = [
            'rsync', '-avm',
            '--exclude=preview-bin/***',
            '--exclude=preview-build/***',
            '--include=*/',
            '--include=*.c',
            '--include=*.h',
            '--include=*.txt',
            '--include=*.cmake',
            '--exclude=*',
            args.source_path + '/',
            target_dir
        ]
        
        log.inf(f"Syncing files from {args.source_path} to {target_dir}")
        log.inf(f"Command: {' '.join(rsync_cmd)}")
        
        try:
            # Execute the rsync command
            result = subprocess.run(rsync_cmd, capture_output=True, text=True)
            
            if result.returncode == 0:
                log.inf("File synchronization completed successfully")
                if result.stdout:
                    log.inf(f"Output: {result.stdout}")
            else:
                log.err(f"rsync failed with return code {result.returncode}")
                if result.stderr:
                    log.err(f"Error: {result.stderr}")
                return result.returncode
                
        except Exception as e:
            log.err(f"Error executing rsync command: {e}")
            return 1
            
        return 0