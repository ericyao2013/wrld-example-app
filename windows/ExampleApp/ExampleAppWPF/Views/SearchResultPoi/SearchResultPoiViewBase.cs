﻿using System;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public abstract class SearchResultPoiViewBase : Control
    {
        protected IntPtr m_nativeCallerPointer;
        protected MainWindow m_currentWindow;

        protected bool m_closing;

        private ControlClickHandler m_closeButtonClickHandler = null;

        public event PropertyChangedEventHandler PropertyChanged;

        public SearchResultPoiViewBase(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            HideAll();
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public override void OnApplyTemplate()
        {
            Button closeButton = (Button)GetTemplateChild("CloseButton");

            m_closeButtonClickHandler = new ControlClickHandler(HandleCloseButtonClicked, closeButton);
        }

        protected void HideAll()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }

        protected void ShowAll()
        {
            Visibility = Visibility.Visible;
            m_currentWindow.DisableInput();
        }

        private void HandleCloseButtonClicked(object sender, MouseButtonEventArgs e)
        {
            if (!m_closing)
            {
                m_closing = true;
                ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
            }
        }

        public abstract void DisplayPoiInfo(Object modelObject, bool isPinned);

        public virtual void DismissPoiInfo()
        {
            HideAll();
        }

        public abstract void UpdateImageData(string url, bool hasImage, byte[] imgData);

        private void HandleCloseClicked(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            ExampleApp.SearchResultPoiViewCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        protected static BitmapImage LoadImageFromByteArray(byte[] imageData)
        {
            if (imageData == null || imageData.Length == 0)
            {
                return null;
            }

            var image = new BitmapImage();

            using (var mem = new MemoryStream(imageData))
            {
                mem.Position = 0;
                image.BeginInit();
                image.CreateOptions = BitmapCreateOptions.PreservePixelFormat;
                image.CacheOption = BitmapCacheOption.OnLoad;
                image.UriSource = null;
                image.StreamSource = mem;
                image.EndInit();
            }

            image.Freeze();

            return image;
        }
    }
}
